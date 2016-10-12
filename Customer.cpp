/*
 * Customer.cpp
 *
 *  Created on: Oct 5, 2016
 *      Author: Joey Bovio, RJ DiNardi
 */

#include "Customer.h"


Customer::Customer(int idnum) {
	transactionTime = SIM_MINUTES_TO_MICROSECONDS * (rand() % 330 + 30);
	id = idnum;
	timer = new Timer();
}

void Customer::enteredLine(){
	timer->start();
}

double Customer::exitedLine(){
	timeSpentInQueue = timer->timePassed();
	return timeSpentInQueue;
}
