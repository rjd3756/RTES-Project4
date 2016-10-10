/*
 * Bank.h
 *
 *  Created on: Oct 5, 2016
 *      Author: rjd3756
 */

#ifndef BANK_H_
#define BANK_H_

#include <cstdlib>
#include <iostream>

#include "Teller.h"
#include "ThreadSafeQueue.h"

class Teller;
class Bank{
public:
	Bank();
	virtual ~Bank();
	static const int OPEN_HOUR = 9; //9 am
	static const int CLOSE_HOUR = 16; //4 pm
	static const int NUMBER_OF_TELLERS = 3;
	static void* start(void* v);
	void customer_enter(Customer c);
	Customer get_next_customer_in_line();
	static void CreateBankThread(Bank* b);
	void TransactionComplete(int tellerId, int customerId, double timeSpentOnTransaction, double timeTellerSpentWaiting);
	bool bank_empty();
	bool isBankOpen();

private:
	int customersServiced;
	int timeSpentInQueue;
	int timeSpentWithTeller;
	int timeTellersSpentWaiting;
	int maxQueueWaitTime;
	int maxTimeTellerWaits;
	int maxTransactionTime;
	int maxQueueDepth;

	pthread_t thread_id;
	ThreadSafeQueue customer_line;
	Teller* tellers[NUMBER_OF_TELLERS];
	pthread_cond_t* availableTellers[NUMBER_OF_TELLERS];
	pthread_mutex_t lock;
	pthread_cond_t customerPresent;

	void execute();
	void open();
};

#endif /* BANK_H_ */
