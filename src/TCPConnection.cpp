#include "TCPConnection.h"

#include <sys/socket.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <unistd.h>

std::string TCPConnection::address() {
	char str[std::max(INET6_ADDRSTRLEN, INET_ADDRSTRLEN)];

	if (_addr.sa_family == AF_INET) {
		// ipv4
		auto addr = (sockaddr_in*)&_addr;
		inet_ntop(AF_INET, &(addr->sin_addr), str, INET_ADDRSTRLEN);
	} else if (_addr.sa_family == AF_INET6) {
		// ipv6
		auto addr = (sockaddr_in6*)&_addr;
		inet_ntop(AF_INET6, &(addr->sin6_addr), str, INET6_ADDRSTRLEN);
	}

	return str;
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

void TCPConnection::read(char* buf, size_t* len) {
	const char msg[] = "hello world";
	memcpy(buf, msg, sizeof(msg));
	*len = sizeof(msg);
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