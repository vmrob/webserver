#pragma once

#include <memory>
#include <thread>

#include "TCPConnection.h"

class ClientConnection {
public:
	ClientConnection(std::unique_ptr<TCPConnection> connection) : _connection(std::move(connection)) {}

	void handle();

private:
	std::unique_ptr<TCPConnection> _connection;
	std::thread _thread;
};