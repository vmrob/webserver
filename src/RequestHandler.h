#pragma once

#include <vector>
#include "ClientConnection.h"

class DocumentStore;

class RequestHandler {
public:
	RequestHandler(DocumentStore* ds) : _ds(ds) {};

	void start();
private:
	std::vector<ClientConnection> _clients;
	DocumentStore* _ds = nullptr;
};