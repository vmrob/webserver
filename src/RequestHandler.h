#pragma once

#include <vector>
#include <mutex>
#include "ClientConnection.h"

class DocumentStore;

class RequestHandler {
public:
	RequestHandler(DocumentStore* ds) : _ds(ds) {};

private:
	DocumentStore* _ds = nullptr;
};