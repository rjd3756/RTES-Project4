/*
 * ThreadSafeQueue.h
 *
 *	A queue that can be accessed by multiple threads safely
 *
 *  Created on: Oct 5, 2016
 *      Author: Joey Bovio, RJ DiNardi
 */
#include <queue>
#include <pthread.h>

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
	void enqueue(Customer c);
	Customer dequeue();
	bool lineEmpty();
	int getCustomerCount();
};

#endif /* THREADSAFEQUEUE_H_ */
