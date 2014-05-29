#include "DocumentStore.h"

std::string gDocumentRoot;

void SetDocumentRoot(std::string documentRoot) {
	gDocumentRoot = documentRoot;
}

std::string GetDocument(std::string uri) {
	return "";
		// "<html>\n"
		// "<head>\n"
		// "  <title>An Example Page</title>\n"
		// "</head>\n"
		// "<body>\n"
		// "  Hello World, this is a very simple HTML document.\n"
		// "</body>\n"
		// "</html>\n";
}