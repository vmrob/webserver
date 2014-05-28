#include "TCPServer.h"

#include <thread>
#include "TCPConnection.h"

void TCPServer::init() {
	// TODO: bind
}

std::shared_ptr<TCPConnection> TCPServer::listen() {
	// TODO: handle new client
	std::this_thread::sleep_for(std::chrono::seconds(2));
	return std::make_shared<TCPConnection>();
}