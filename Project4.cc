#include <cstdlib>
#include <iostream>
#include <Teller.h>

int main(int argc, char *argv[]) {
	std::cout << "Welcome to the QNX Momentics IDE" << std::endl;
	Teller* t = new Teller();
	(*t).Create();
	(*t).Create();
	return EXIT_SUCCESS;
}
