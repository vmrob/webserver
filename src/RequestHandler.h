#pragma once

class DocumentStore;

class RequestHandler {
public:
	RequestHandler(DocumentStore* ds) : _ds(ds) {};

	void start();
private:
	DocumentStore* _ds = nullptr;
};