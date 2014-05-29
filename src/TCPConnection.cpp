#include "TCPConnection.h"

#include <sys/socket.h>
#include <fcntl.h>
#include <unistd.h>

std::string TCPConnection::address() {
	return "[address here]";
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