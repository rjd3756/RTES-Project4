#include <cstdlib>
#include <iostream>
#include <unistd.h>
#include "Customer.h"
#include <pthread.h>
#include "Bank.h"

const double TIME_CONVERSION = 100000/60; //simulation minutes to microseconds


int main(int argc, char *argv[]) {
	std::cout << "Welcome to the QNX Momentics IDE" << std::endl;
	Bank* bank = new Bank();
	Bank::CreateBankThread(bank);

	while(1) {
		Customer customer = Customer::Customer();
		int customer_enter_wait = rand() % 180 + 60;
		usleep(customer_enter_wait * TIME_CONVERSION);

		bank->customer_enter(customer);
	}
	return EXIT_SUCCESS;
}
