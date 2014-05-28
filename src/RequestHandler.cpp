#include "RequestHandler.h"

#include <iostream>
#include "TCPServer.h"
#include "TCPConnection.h"

#define LISTEN_PORT 8080

void RequestHandler::start() {

	TCPServer server(LISTEN_PORT);
	try {
		server.init();
	} catch (std::runtime_error& e) {
		std::cout << e.what() << std::endl;
		return;
	}

	while (true) {
		std::cout << "waiting for connection" << std::endl;
		auto connection = server.listen();
		if (!connection) {
			continue;
		}
		std::cout << "client connected from " << connection->address() << std::endl;
		_clients.emplace_back(connection);
		_clients.back().handle();
	}

}