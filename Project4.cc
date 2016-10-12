#include <cstdlib>
#include <iostream>
#include <unistd.h>
#include "Customer.h"
#include <pthread.h>
#include "Bank.h"
#include "Constants.h"


int main(int argc, char *argv[]) {
	srand(time(0));
	std::cout << "Welcome to the QNX Momentics IDE" << std::endl;
	Bank* bank = new Bank(CLOSE_HOUR - OPEN_HOUR);
	Bank::CreateBankThread(bank);

	//wait until the bank thread is ready
	pthread_mutex_t lock;
	while(!bank->ready){
		pthread_cond_wait(&bank->readyCondition, &lock);
	}

	int i = 0;
	while(bank->isBankOpen()) {
		Customer customer = Customer::Customer(i);
		int customer_enter_wait = rand() % 180 + 60;
		usleep(customer_enter_wait * SIMULATION_TIME_CONVERSION_MIN_TO_MICRO);

		bank->customer_enter(customer);
		i++;
	}
	std::cout << "Bank closed" << std::endl;
	bank->displayMetrics();
	for (int i = 0; i < 10; i++);
	return EXIT_SUCCESS;
}
