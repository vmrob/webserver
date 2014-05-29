#pragma once

#include <memory>
#include <string>
#include <netinet/in.h>

#define TIMEOUT 1000

class TCPConnection {
public:
	~TCPConnection();

	std::string address();

	void accept(int sockd);

	// nonblocking, will read a max of len bytes to buffer.
	// len will contain amount written
	void read(char* buf, size_t* len);

	void write(const char* buf, size_t len);
	void close();

private:
	sockaddr _addr;
	socklen_t _addrlen = sizeof(_addr);
	int _sockd = 0;
};