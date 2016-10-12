/*
 * Bank.cpp
 *
 *  Created on: Oct 5, 2016
 *      Author: rjd3756
 */

#include "Bank.h"


Bank::Bank(int hoursOpen){
	minutesToRun = hoursOpen * SIM_HOURS_TO_SIM_MINUTES;
	std::cout << "New bank" << std::endl;
	customer_line = ThreadSafeQueue::ThreadSafeQueue();
	pthread_cond_init(&customerPresent, NULL);
	pthread_cond_init(&readyCondition, NULL);
	pthread_cond_init(&allCustomersServicedCondition, NULL);
	ready = false;
}

void* Bank::start(void* v){
	Bank* b = (Bank*)v;
	std::cout << "Bank Thread Started" << std::endl;
	b->execute();
}

void Bank::execute() {
	std::cout << "Bank Execute" << std::endl;

	//hire tellers
	for(int i = 0; i < NUMBER_OF_TELLERS; ++i){
		tellers[i] = new Teller(this, i, customerPresent, lock);
	}

	//(9 am) begin servicing customers today
	open();
}


void Bank::open(){
	//std::cout << "Bank open" << std::endl;
	timer = new Timer();
	timer->start();

	for(int i = 0; i < NUMBER_OF_TELLERS; ++i){
		Teller::CreateTellerThread(tellers[i]);
	}
	ready = true;
	pthread_cond_signal(&readyCondition);

}

bool Bank::isBankOpen() {
	double currentTime = timer->timePassed();// * SECONDS_TO_SIMULATION_HOURS;
	//std::cout << "Sim time: " << currentTime * SECONDS_TO_SIM_MINUTES << std::endl;
	return currentTime * SECONDS_TO_SIM_MINUTES < minutesToRun;
}

void Bank::customer_enter(Customer c) {
	if (isBankOpen()) {
		allCustomersServiced = false;
		c.EnteredLine();
		customer_line.Enqueue(c);
		int lineLength = customer_line.getCustomerCount();
		if(lineLength > maxQueueDepth){
			maxQueueDepth = lineLength;
		}
		std::cout << "Customer entered " << c.id << std::endl;
		pthread_cond_signal(&customerPresent);
	}
}

bool Bank::bank_empty() {
	//std::cout << "Customer Count " << customer_line.getCustomerCount() << std::endl;
	bool isEmpty = customer_line.line_empty();
	if(isEmpty){
		pthread_cond_signal(&allCustomersServicedCondition);
		allCustomersServiced = true;
	}

	return isEmpty;
}

Customer Bank::get_next_customer_in_line(){
	Customer c = customer_line.Dequeue();
	c.ExitedLine();
	return c;
}

void Bank::TransactionComplete(int tellerId, int customerId, double timeSpentOnTransaction, double timeTellerWaited, double timeCustomerSpentWaiting){
	std::cout << "Teller" << tellerId << " completed transaction with customer " << customerId << ". Time spent: " <<
			timeSpentOnTransaction << std::endl << std::flush;
	pthread_mutex_lock(&lock);

	++customersServiced;

	timeSpentWithTeller += timeSpentOnTransaction;
	if(timeSpentOnTransaction > maxTransactionTime){
		maxTransactionTime = timeSpentOnTransaction;
	}

	timeTellersSpentWaiting += timeTellerWaited;
	if(timeTellerWaited > maxTimeTellerWaits){
		maxTimeTellerWaits = timeTellerWaited;
	}

	timeSpentInQueue += timeCustomerSpentWaiting;
	if(timeCustomerSpentWaiting > maxQueueWaitTime){
		maxQueueWaitTime = timeCustomerSpentWaiting;
	}

	pthread_mutex_unlock(&lock);
}

void Bank::displayMetrics(){
	pthread_mutex_t lock;
	while(!allCustomersServiced){
		pthread_cond_wait(&allCustomersServicedCondition, &lock);
	}

	std::cout << "Total Customers Serviced:  " << customersServiced << std::endl;
	std::cout << "Total time spent in queue:  " << timeSpentInQueue << std::endl;
	std::cout << "Average Time Customer Spends in Queue:  " << ((double)timeSpentInQueue)/customersServiced << std::endl;
	std::cout << "Average Time Customer Spends with Teller:  " << ((double)timeSpentWithTeller)/customersServiced << std::endl;
	std::cout << "Average Time Tellers Wait for Customers:  " << ((double)timeTellersSpentWaiting)/customersServiced << std::endl;
	std::cout << "Max Customer Wait Time in Queue:  " << maxQueueWaitTime << std::endl;
	std::cout << "Max Time Tellers Wait for Customers:  " << maxTimeTellerWaits << std::endl;
	std::cout << "Max Transaction Time for Tellers:  " << maxTransactionTime << std::endl;
	std::cout << "Max Depth of Queue:  " << maxQueueDepth << std::endl;
}

Bank::~Bank() {
	pthread_cancel(thread_id);
}

void Bank::CreateBankThread(Bank* b){
	pthread_t thread;
	pthread_create(&thread, NULL, &Bank::start, (void*)b);
}
