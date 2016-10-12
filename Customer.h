/*
 * Customer.h
 *
 *	Represents a customer
 *
 *  Created on: Oct 5, 2016
 *      Author: Joey Bovio, RJ DiNardi
 */
#include <stdlib.h>
#include "Constants.h"
#include "Timer.h"

#ifndef CUSTOMER_H_
#define CUSTOMER_H_

class Customer {
public:
	Timer* timer;
	int id;
	double transactionTime;
	double timeEntered;
	double timeSpentInQueue;

	//creates a new customer with the given id
	Customer(int idnum);

	//handles when a customer enters the line
	void enteredLine();

	//handles when a customer exits the line and returns how long it was in line
	double exitedLine();
};

#endif /* CUSTOMER_H_ */
