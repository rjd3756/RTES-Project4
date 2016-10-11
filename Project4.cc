#include <cstdlib>
#include <iostream>
#include <unistd.h>
#include "Customer.h"
#include <pthread.h>
#include "Bank.h"
#include "Constants.h"


int main(int argc, char *argv[]) {
	std::cout << "Welcome to the QNX Momentics IDE" << std::endl;
	Bank* bank = new Bank(CLOSE_HOUR - OPEN_HOUR);
	Bank::CreateBankThread(bank);

	int i = 0;
	while(i < 10) {
		Customer customer = Customer::Customer(i);
		int customer_enter_wait = rand() % 180 + 60;
		usleep(customer_enter_wait * SIMULATION_TIME_CONVERSION_MIN_TO_MICRO);

		bank->customer_enter(customer);
		i++;
	}
	for (int i = 0; i < 10; i++);
	return EXIT_SUCCESS;
}
