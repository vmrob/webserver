#include "TCPServer.h"

#include <thread>
#include <iostream>
#include <cstdio>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

#include "TCPConnection.h"
#include "ClientConnection.h"

void TCPServer::_init() {
	_sockd = socket(AF_INET, SOCK_STREAM, 0);
	if (_sockd == -1) {
		throw std::runtime_error("socket error: " + std::string(strerror(errno)));
	}

	sockaddr_in address;

	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(_port);

	int status = bind(_sockd, (sockaddr*)&address, sizeof(address));
	if (status == -1) {
		close(_sockd);
		_sockd = 0;
		throw std::runtime_error("bind error: " + std::string(strerror(errno)));
	}

	status = listen(_sockd, 5);
	if (status == -1) {
		close(_sockd);
		_sockd = 0;
		throw std::runtime_error("listen error: " + std::string(strerror(errno)));
	}
}

void TCPServer::start() {

	try {
		_init();
	} catch (std::runtime_error& e) {
		std::cout << e.what() << std::endl;
		return;
	}

	while (true) {
		std::cout << "waiting for connection" << std::endl;
		auto c = _accept();
		std::cout << "client connected from " << c->address() << std::endl;
		std::thread([](std::unique_ptr<TCPConnection> c){
			ClientConnection(std::move(c)).handle();
		}, std::move(c)).detach();
	}
}

std::unique_ptr<TCPConnection> TCPServer::_accept() {
	std::unique_ptr<TCPConnection> connection(new TCPConnection());
	connection->accept(_sockd);
	return connection;
}