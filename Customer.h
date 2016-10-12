/*
 * Customer.h
 *
 *  Created on: Oct 5, 2016
 *      Author: rjd3756
 */
#include <stdlib.h>
#include "Constants.h"
#include "Timer.h"

#ifndef CUSTOMER_H_
#define CUSTOMER_H_

class Customer {
public:
	Customer(int idnum);
	void EnteredLine();
	double ExitedLine();
	Timer* timer;
	int id;
	double transactionTime;
	double timeEntered;
	double timeSpentInQueue;
};

#endif /* CUSTOMER_H_ */
