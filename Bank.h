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
#include "Runnable.h"

class Bank : public Runnable{
private:
	int customersServiced;
	int timeSpentInQueue;
	int timeSpentWithTeller;
	int maxQueueWaitTime;
	int maxTimeTellerWaits;
	int maxTransactionTime;
	int maxQueueDepth;

	pthread_t thread_id;
	static ThreadSafeQueue customer_line;
	static Teller tellers[];

	static void* execute(void*);
	static void open();

public:
	Bank();
	virtual ~Bank();
	static const int OPEN_HOUR = 9; //9 am
	static const int CLOSE_HOUR = 16; //4 pm
	static const int NUMBER_OF_TELLERS = 3;
	virtual void start();
	void customer_enter();
};

#endif /* BANK_H_ */
