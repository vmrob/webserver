#include "ClientConnection.h"

#include <iostream>
#include <cstdlib>
#include "TCPConnection.h"

void ClientConnection::handle() {
	size_t bufSize = 1024;
	std::unique_ptr<char> buf((char*)calloc(bufSize, 1));

	_connection->read(buf.get(), &bufSize);

	std::cout << std::string(buf.get(), bufSize) << std::endl;

	char hello[] =
		"HTTP/1.1 200 OK\r\n"
		"Connection: close\r\n"
		"\r\n"
		"<html>\n"
		"<head>\n"
		"  <title>An Example Page</title>\n"
		"</head>\n"
		"<body>\n"
		"  Hello World, this is a very simple HTML document.\n"
		"</body>\n"
		"</html>\n";

	_connection->write(hello, sizeof(hello));
	_connection->close();

	std::cout << "handled client" << std::endl;
}