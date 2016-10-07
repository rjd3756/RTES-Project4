/*
 * Bank.h
 *
 *  Created on: Oct 5, 2016
 *      Author: rjd3756
 */

#ifndef BANK_H_
#define BANK_H_

class Bank {
private:
	int customersServiced;
	int timeSpentInQueue;
	int timeSpentWithTeller;
	int maxQueueWaitTime;
	int maxTimeTellerWaits;
	int maxTransactionTime;
	int maxQueueDepth;

public:
	Bank();
	virtual ~Bank();
	static const int openHour = 9; //9 am
	static const int closeHour = 16; //4 pm
};

#endif /* BANK_H_ */
