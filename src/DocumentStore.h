#pragma once

#include <string>

class DocumentStore {
public:
	DocumentStore(std::string documentRoot) : _documentRoot(std::move(documentRoot)) {}

private:
	std::string _documentRoot;
};