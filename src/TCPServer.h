#pragma once

#include <memory>

class TCPConnection;

class TCPServer {
public:
	TCPServer(int port) : _port(port) {}

	void start();

private:
	int _port = 0;
	int _sockd = 0;


	void _init();
	std::unique_ptr<TCPConnection> _accept();
};