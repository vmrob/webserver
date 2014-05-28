#pragma once

#include <memory>

class TCPConnection;

class TCPServer {
public:
	TCPServer(int port) : _port(port) {}
	
	// must be called before listen
	// throws on error
	void init();

	std::shared_ptr<TCPConnection> listen();

private:
	int _port = 0;
};