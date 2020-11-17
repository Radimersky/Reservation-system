#include "handler.h"

int main() {

	try {
		Handler().handle();
	} catch (std::runtime_error& ex) {
		std::cerr << "Exception: " << ex.what() << '\n';
	}

	return 0;
}
