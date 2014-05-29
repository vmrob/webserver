#include "TCPConnection.h"

#include <sys/socket.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <unistd.h>
#include <cerrno>

#define BUFFER_SIZE 1024

TCPConnection::TCPConnection()
	: _buffer(BUFFER_SIZE)
{}

std::string TCPConnection::address() {
	char str[std::max(INET6_ADDRSTRLEN, INET_ADDRSTRLEN)];

	if (_addr.sa_family == AF_INET) {
		// ipv4
		auto addr = (sockaddr_in*)&_addr;
		inet_ntop(AF_INET, &(addr->sin_addr), str, INET_ADDRSTRLEN);
		return str;
	} else if (_addr.sa_family == AF_INET6) {
		// ipv6
		auto addr = (sockaddr_in6*)&_addr;
		inet_ntop(AF_INET6, &(addr->sin6_addr), str, INET6_ADDRSTRLEN);
		return str;
	}

	return "[unknown address format]";
}

void TCPConnection::accept(int sockd) {
	_sockd = -1;
	while (_sockd == -1) {
		_sockd = ::accept(sockd, (sockaddr*)&_addr, &_addrlen);
		if (_sockd == -1) {
			perror("Wrong connection");
		}
	}
	fcntl(_sockd, F_SETFL, O_NONBLOCK);
}

size_t TCPConnection::nonblockingRead(char* buf, size_t len) {
	size_t remaining = len;
	char* ptr = buf;

	while (remaining > 0) {
		if (_buffer.size() > 0) {
			size_t copied = std::min(len, _buffer.size());
			std::copy(_buffer.begin(), _buffer.begin() + copied, ptr);
			remaining -= copied;
			ptr += copied;

			_buffer.erase(_buffer.begin(), _buffer.begin() + copied);
			continue;
		}
		_doTcpRead();
	}
	return ptr - buf;
}

size_t TCPConnection::readUntil(char* buf, size_t len, char delim) {
	size_t written = 0;
	char c = '\0';
	while (written < len) {
		readByte(&c);
		if (c == delim) {
			return written;
		}
		buf[written++] = c;
	}
	return written;
}

size_t TCPConnection::nonblockingReadByte(char* buf) {
	if (_buffer.size() == 0) {
		_doTcpRead();
	}
	if (_buffer.size() == 0) {
		return 0;
	}
	buf[0] = *_buffer.begin();
	_buffer.pop_front();
	return 1;
}

size_t TCPConnection::readByte(char* buf) {
	while (nonblockingReadByte(buf) == 0) {
		// nop
	}
	return 1;
}

size_t TCPConnection::_doTcpRead() {
	char buf[BUFFER_SIZE] = {};
	_buffer.clear();

	timeval timeout = {};
	timeout.tv_usec = 100000; // 100ms
	fd_set readfds;
	FD_ZERO(&readfds);
	FD_SET(_sockd, &readfds);

	int sel = select(_sockd + 1, &readfds, nullptr, nullptr, &timeout);
	if (sel == -1) {
		close();
		throw std::runtime_error("select error: " + std::string(strerror(errno)));
	}
	if (sel == 0) {
		return 0;
	}

	size_t received = recv(_sockd, buf, BUFFER_SIZE, 0);

	if (received) {
		_buffer.insert(_buffer.end(), buf, buf + received);	
	}

	return received;
}

TCPConnection::~TCPConnection() {
	close();
}

void TCPConnection::write(const char* buf, size_t len) {
	::write(_sockd, buf, len);
}

void TCPConnection::close() {
	if (_sockd) {
		::close(_sockd);
		_sockd = 0;
	}	
}