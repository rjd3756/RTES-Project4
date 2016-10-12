/*
 * ThreadSafeQueue.h
 *
 *  Created on: Oct 5, 2016
 *      Author: rjd3756
 */
#include <queue>
#include <pthread.h>
#include <cstdlib>
#include <iostream>
#include "Customer.h"


#ifndef THREADSAFEQUEUE_H_
#define THREADSAFEQUEUE_H_

class ThreadSafeQueue {
private:
	std::queue<Customer> queue;
	int customer_count;
	pthread_mutex_t lock;

public:
	ThreadSafeQueue();
	void Enqueue(Customer c);
	Customer Dequeue();
	bool line_empty();
	int getCustomerCount();
};

#endif /* THREADSAFEQUEUE_H_ */
