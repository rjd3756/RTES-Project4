/*
 * Thread.h
 *
 *  Created on: Oct 5, 2016
 *      Author: rjd3756
 */

#ifndef THREAD_H_
#define THREAD_H_

#include<pthread.h>
#include<iostream>

#include "Bank.h"

class Bank;
class Teller{
private:

	pthread_cond_t isAvailable;
	Bank* bank;

	void serve_customers();

public:
	static void* start(void* v);
	Teller(Bank* b);
	static void CreateTellerThread(Teller* t);
};

#endif /* THREAD_H_ */
