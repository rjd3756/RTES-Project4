/*
 * Bank.cpp
 *
 *  Created on: Oct 5, 2016
 *      Author: rjd3756
 */

#include "Bank.h"


Bank::Bank(int hoursOpen){
	hoursToRun = hoursOpen;
	std::cout << "New bank" << std::endl;
	customer_line = ThreadSafeQueue::ThreadSafeQueue();
	pthread_cond_init(&customerPresent, NULL);
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
	for(int i = 0; i < NUMBER_OF_TELLERS; ++i){
		Teller::CreateTellerThread(tellers[i]);
	}


}

bool Bank::isBankOpen() {
	// TODO: Return true/false based on time of day
	return true;
}

void Bank::customer_enter(Customer c) {
	if (isBankOpen()) {
		c.EnteredLine();
		customer_line.Enqueue(c);
		std::cout << "Customer entered " << c.id << std::endl;
		pthread_cond_signal(&customerPresent);
	}
}

bool Bank::bank_empty() {
	return customer_line.line_empty();
}

Customer Bank::get_next_customer_in_line(){
	Customer c = customer_line.Dequeue();
	c.ExitedLine();
	return c;
}

void Bank::TransactionComplete(int tellerId, int customerId, double timeSpentOnTransaction, double timeTellerSpentWaiting, double timeCustomerSpentWaiting){
	std::cout << "Teller" << tellerId << " completed transaction with customer " << customerId << ". Time spent: " <<
			timeSpentOnTransaction << std::endl << std::flush;
	std::cout << "Teller" << tellerId << " waited " << timeTellerSpentWaiting << " for customer" << std::endl << std::flush;
	pthread_mutex_lock(&lock);

	++customersServiced;

	timeSpentWithTeller += timeSpentOnTransaction;
	if(timeSpentOnTransaction > maxTransactionTime){
		maxTransactionTime = timeSpentOnTransaction;
	}

	timeTellerSpentWaiting += timeTellerSpentWaiting;
	if(timeTellerSpentWaiting > maxTimeTellerWaits){
		maxTimeTellerWaits = timeTellerSpentWaiting;
	}

	timeSpentInQueue += timeCustomerSpentWaiting;
	if(timeCustomerSpentWaiting > timeSpentInQueue){
		maxQueueWaitTime = timeCustomerSpentWaiting;
	}

	pthread_mutex_unlock(&lock);
}

Bank::~Bank() {
	pthread_cancel(thread_id);
}

void Bank::CreateBankThread(Bank* b){
	pthread_t thread;
	pthread_create(&thread, NULL, &Bank::start, (void*)b);
}
