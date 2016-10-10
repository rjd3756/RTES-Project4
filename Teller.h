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
#include <unistd.h>

#include "Bank.h"
#include "Timer.h"

class Bank;
class Teller{
private:

	pthread_cond_t customerPresent;
	pthread_mutex_t lock;
	Bank* bank;
	int id;

	void serve_customers();

public:
	static void* start(void* v);
	Teller(Bank* b, int idnum, pthread_cond_t custPresent, pthread_mutex_t mutex);
	static void CreateTellerThread(Teller* t);
};

#endif /* THREAD_H_ */
