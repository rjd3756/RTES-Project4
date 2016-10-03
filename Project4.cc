#include <cstdlib>
#include <iostream>
#include "Thread.cpp"
#include "Banker.cpp"

int main(int argc, char *argv[]) {
	std::cout << "Welcome to the QNX Momentics IDE" << std::endl;
	Banker t = new Banker();
	t.Create();
	return EXIT_SUCCESS;
}
