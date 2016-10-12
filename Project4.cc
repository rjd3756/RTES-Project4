#include <cstdlib>
#include <iostream>
#include <unistd.h>
#include <pthread.h>
#include "Bank.h"
#include "Customer.h"
#include "Constants.h"

static const int customerEnterMinTime = 60;
static const int customerEnterMaxTime = 240;

int main(int argc, char *argv[]) {
	srand(time(0));
	Bank* bank = new Bank(CLOSE_HOUR - OPEN_HOUR);
	Bank::createBankThread(bank);

	//wait until the bank thread is ready
	pthread_mutex_t lock;
	while(!bank->ready){
		pthread_cond_wait(&bank->readyCondition, &lock);
	}

	//create more customers while the bank is open
	int i = 0;
	while(bank->isBankOpen()) {
		Customer customer = Customer::Customer(i);
		int customer_enter_wait = rand() % (customerEnterMaxTime - customerEnterMinTime) + customerEnterMinTime;
		usleep(customer_enter_wait * SIM_MINUTES_TO_MICROSECONDS);

		bank->customerEnter(customer);
		i++;
	}

	//display metrics
	std::cout << "Bank closed" << std::endl;
	bank->displayMetrics();

	return EXIT_SUCCESS;
}
