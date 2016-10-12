/*
 * Bank.h
 *
 *	Represents a bank in the context of the program
 *
 *  Created on: Oct 5, 2016
 *      Author: Joey Bovio, RJ DiNardi
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
	static const int NUMBER_OF_TELLERS = 3;

	//thread coordination variables
	pthread_cond_t readyCondition;
	pthread_cond_t allCustomersServicedCondition;
	bool ready;
	bool allCustomersServiced;

	//Functions to help create a new bank thread
	static void* start(void* v);
	static void createBankThread(Bank* b);

	//Handles when a customer enters the bank
	void customerEnter(Customer c);

	//returns the next customer in line
	Customer getNextCustomerInLine();

	//handles when the transaction with the customer is complete
	void transactionComplete(int tellerId, int customerId, double timeSpentOnTransaction, double timeTellerWaited, double timeCustomerSpentWaiting);

	//returns if the bank is empty
	bool bankEmpty();

	//returns if the bank is open
	bool isBankOpen();

	//displays metrics
	void displayMetrics();

	//Create a new bank and give how many hours it is open
	Bank(int hoursOpen);
	virtual ~Bank();

private:
	//metrics variables
	int customersServiced;
	double timeSpentInQueue;
	double timeSpentWithTeller;
	double timeTellersSpentWaiting;
	double maxQueueWaitTime;
	double maxTimeTellerWaits;
	double maxTransactionTime;
	int maxQueueDepth;

	int minutesToRun;

	//the timer keeping track of how long the bank has been open
	Timer* timer;

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
