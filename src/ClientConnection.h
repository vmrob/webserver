#pragma once

#include <memory>

class TCPConnection;

class ClientConnection {
public:
	ClientConnection(std::shared_ptr<TCPConnection> connection) : _connection(connection) {}

	void handle();

private:
	std::shared_ptr<TCPConnection> _connection;
};