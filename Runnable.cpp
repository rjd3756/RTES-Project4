/*
 * Runnable.cpp
 *
 *  Created on: Oct 7, 2016
 *      Author: rjd3756
 */
#include <pthread.h>
#include <cstdlib>
#include <iostream>

#include "Runnable.h"
#include "Bank.h"

void* Runnable::call_start(void* runnable_ref){
	std::cout << "call start" << std::endl;

	Runnable *r = (Runnable *)runnable_ref;
	std::cout << r << std::endl;
	Bank *b = (Bank *)r;
	std::cout << b->NUMBER_OF_TELLERS << std::endl;
	r->start();
}

void Runnable::create_thread(Runnable* r){
	std::cout << "create thread" << std::endl;

	int thread_id;
	pthread_create(&thread_id, NULL, &call_start, &r);
}

void Runnable::start(){
	std::cout << "runnable start" << std::endl;
}
