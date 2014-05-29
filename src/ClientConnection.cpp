#include "ClientConnection.h"

#include <array>
#include <iostream>
#include <cstdlib>
#include "TCPConnection.h"

void ClientConnection::handle() try {
	std::string line;
	char buf[1024] = {};

	bool lineComplete = false;
	while (!lineComplete) {
		size_t written = _connection->readUntil(buf, sizeof(buf) - 1, '\r');

		char c = '\0';
		_connection->readByte(&c);
		if (c == '\n') {
			lineComplete = true;
		} else {
			throw std::runtime_error("invalid http request: carraige return without newline");
		}
		line.insert(line.end(), buf, buf + written);
	}

	line.push_back('\0');

	std::cout << line << std::endl;


	// while (true) {
	// 	_connection->readByte(&c);
	// 	if (r) {
	// 		if (c == '\n') {
	// 			break;
	// 		}
	// 		// invalid header? \r without \n
	// 		throw std::runtime_error("invalid http request: carraige return without newline");
	// 	}
	// 	if (c == '\n') {
	// 		// invalid header? \n without \r preceeding it
	// 		throw std::runtime_error("invalid http request: newline without preceeding carraige return");
	// 	}
	// 	if (c == '\r') {
	// 		r = true;
	// 		continue;
	// 	}
	// 	line.push_back(c);
	// }

	
		// size_t readSize = buf.size() - nextWrite;

		// _connection->read(buf.data() + nextWrite, &readSize);

		// std::cout << "read " << readSize << " bytes:" << std::endl;
		// std::cout << std::string(buf.data() + nextWrite, readSize) << std::endl;

		// size_t pos = 0;
		// while (pos < readSize) {
		// 	if (buf[pos] == '\r') {
		// 		if (pos < readSize - 1) {
		// 			if (buf[pos + 1] == '\n') {
		// 				// end of line, drop until double carraige return + newline

		// 				nextWrite = 0;
		// 				break;
		// 			}
		// 			// read error, \r without \n
		// 			throw std::runtime_error("invalid http request: carraige return without newline")
		// 		} else {
		// 			// \r is the last character in the buffer
		// 			buf[0] = '\r';
		// 			nextWrite = 1;
		// 			break;
		// 		}
		// 	}
		// 	line.push_back(buf[pos]);
		// }

		// auto r = std::find(buf.begin(), buf.begin() + readSize, '\r');
		// line.insert(line.end(), buf.begin(), r);

		// if (r != buf.begin() + readSize &&
		// 	r != buf.begin() + readSize - 1
		// ) {
		// 	if (*(r + 1) == '\n') {
		// 	}
		// }

		// std::string method;
		// std::string uri;
		// for (size_t i = 0; i < readSize; ++i) {
		// 	if 
		// }
		
	// }



	// char hello[] =
	// 	"HTTP/1.1 200 OK\r\n"
	// 	"Connection: close\r\n"
	// 	"\r\n"
	// 	"<html>\n"
	// 	"<head>\n"
	// 	"  <title>An Example Page</title>\n"
	// 	"</head>\n"
	// 	"<body>\n"
	// 	"  Hello World, this is a very simple HTML document.\n"
	// 	"</body>\n"
	// 	"</html>\n";

	// _connection->write(hello, sizeof(hello));
	// _connection->close();

	std::cout << "handled client" << std::endl;
} catch (std::runtime_error& e) {
	_connection->close();
	std::cout << e.what() << std::endl;
	return;
}
