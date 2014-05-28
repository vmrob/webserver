#include <string>

#include "RequestHandler.h"
#include "DocumentStore.h"

int main(int argc, char* argv[]) {

	std::string documentRoot = ".";

	if (argc == 2) {
		documentRoot = argv[1];
	}

	DocumentStore ds(documentRoot);
	RequestHandler rh(&ds);

	rh.start();
}