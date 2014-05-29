#include <string>

#include "RequestHandler.h"
#include "DocumentStore.h"
#include "TCPServer.h"

#define LISTEN_PORT 8080

int main(int argc, char* argv[]) {

	std::string documentRoot = ".";

	if (argc == 2) {
		documentRoot = argv[1];
	}

	DocumentStore ds(documentRoot);
	RequestHandler rh(&ds);

	TCPServer server(LISTEN_PORT);

	server.start();
}