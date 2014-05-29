#pragma once

#include <memory>
#include <string>
#include <netinet/in.h>
#include <boost/circular_buffer.hpp>

#define TIMEOUT 1000

class TCPConnection {
public:
	TCPConnection();
	~TCPConnection();

	std::string address();

	void accept(int sockd);

	// nonblocking, will read a max of len bytes to buffer.
	// returns amount written
	// throws on error
	size_t nonblockingRead(char* buf, size_t len);

	// nonblocking, will read a max of 1 byte to buffer.
	// much faster than reading a single byte from the socket
	// returns amount written
	// throws on error
	size_t nonblockingReadByte(char* buf);

	size_t readByte(char* buf);

	// blocking, reads until either len bytes have been read or until delim is found
	// delim is discarded from stream
	// returns amount written
	// throws on error
	size_t readUntil(char* buf, size_t len, char delim);

	void write(const char* buf, size_t len);
	void close();

private:
	sockaddr _addr = {};
	socklen_t _addrlen = sizeof(_addr);
	int _sockd = 0;

	boost::circular_buffer<char> _buffer;

	// will clear buffer and read until full or until timeout occurs.
	// returns amount read
	size_t _doTcpRead();
};