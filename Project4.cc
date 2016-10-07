#include <cstdlib>
#include <iostream>
#include <unistd.h>
#include "Customer.h"
#include <pthread.h>
#include "Runnable.h"
#include "Bank.h"

const double TIME_CONVERSION = 100000/60; //simulation minutes to microseconds


int main(int argc, char *argv[]) {
	std::cout << "Welcome to the QNX Momentics IDE" << std::endl;

	Runnable::create_thread(new Bank());

	while(1) {
		Customer customer = Customer::Customer();
		int customer_enter_wait = rand() % 180 + 60;
		usleep(customer_enter_wait * TIME_CONVERSION);

	}
	return EXIT_SUCCESS;
}
