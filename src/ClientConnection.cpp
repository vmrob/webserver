#include "ClientConnection.h"

#include <array>
#include <iostream>
#include <cstdlib>

#include "TCPConnection.h"
#include "DocumentStore.h"

std::string ClientConnection::_readCrlfLine() {
	std::string line;
	char buf[1024] = {};

	bool lineComplete = false;
	while (!lineComplete) {
		size_t written = _connection->readUntil(buf, sizeof(buf), '\r');

		if (written < sizeof(buf)) {
			char c = '\0';
			_connection->readByte(&c);
			if (c == '\n') {
				lineComplete = true;
			} else {
				throw std::runtime_error("invalid http request: carraige return without newline");
			}
		}
		line.insert(line.end(), buf, buf + written);
	}

	return line;
}

void ClientConnection::handle() try {
	std::string request = _readCrlfLine();

	// read until an empty line is found, end of request
	while (_readCrlfLine() != "") {
		// nop
	}

	// stream is now ready for next request

	size_t firstSpace = request.find(' ');
	if (firstSpace == std::string::npos || firstSpace == request.size()) {
		throw std::runtime_error(std::string("invalid http request header: ") + request);
	}
	size_t secondSpace = request.find(' ', firstSpace + 1);
	if (firstSpace == std::string::npos || secondSpace == request.size()) {
		throw std::runtime_error(std::string("invalid http request header: ") + request);
	}
	std::string method(request, 0, firstSpace);
	std::string uri(request, firstSpace + 1, secondSpace - firstSpace - 1);

	if (method != "GET" && method != "HEAD") {
		const char response[] =
			"HTTP/1.1 501 Not Implemented\r\n"
			"Connection: close\r\n"
			"\r\n";
		_connection->write(response, sizeof(response));
		_connection->close();
		return;
	}

	auto doc = GetDocument(uri);

	if (doc.empty()) {
		const char response[] =
			"HTTP/1.1 404 Not Found\r\n"
			"Connection: close\r\n"
			"\r\n";
		_connection->write(response, sizeof(response));
		_connection->close();
		return;
	}	

	std::string response =
		"HTTP/1.1 200 OK\r\n"
		"Content-Length: " + std::to_string(doc.size()) + "\r\n"
		"Connection: close\r\n"
		"\r\n";

	if (method == "GET") {
		response += doc;	
	}

	_connection->write(response.c_str(), response.size());
	_connection->close();

} catch (std::runtime_error& e) {
	_connection->close();
	std::cout << e.what() << std::endl;
	return;
}
