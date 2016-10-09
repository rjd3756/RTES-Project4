/*
 * Bank.cpp
 *
 *  Created on: Oct 5, 2016
 *      Author: rjd3756
 */

#include "Bank.h"


Bank::Bank(){
	std::cout << "New bank" << std::endl;
	customer_line = ThreadSafeQueue::ThreadSafeQueue();
}

void* Bank::start(void* v){
	Bank* b = (Bank*)v;
	std::cout << "Bank Started" << std::endl;
	b->execute();
}

void Bank::execute() {
	std::cout << "Bank Execute" << std::endl;
	//hire tellers
	for(int i = 0; i < NUMBER_OF_TELLERS; ++i){
		pthread_cond_t isAvailable;
		availableTellers[i] = &isAvailable;
		pthread_cond_init(&isAvailable, NULL);
		tellers[i] = new Teller(this);
	}

	//(9 am) begin servicing customers today
	open();
}


void Bank::open(){
	for(int i = 0; i < NUMBER_OF_TELLERS; ++i){
		Teller::CreateTellerThread(tellers[i]);
	}
}

void Bank::customer_enter(Customer c) {
	customer_line.Enqueue(c);
}

Customer Bank::get_next_customer_in_line(){
	//TODO Add time spent in queue
	return customer_line.Dequeue();
}

void Bank::TransactionComplete(double timeSpentOnTransaction, double timeTellerSpentWaiting){
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

	pthread_mutex_unlock(&lock);
}

Bank::~Bank() {
	pthread_cancel(thread_id);
}

void Bank::CreateBankThread(Bank* b){
	pthread_t thread;
	pthread_create(&thread, NULL, &Bank::start, (void*)b);
}
