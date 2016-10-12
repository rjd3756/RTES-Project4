/*
 * ThreadSafeQueue.cpp
 *
 *  Created on: Oct 5, 2016
 *      Author: Joey Bovio, RJ DiNardi
 */
#include "ThreadSafeQueue.h"



ThreadSafeQueue::ThreadSafeQueue() {
	customer_count = 0;
}

void ThreadSafeQueue::enqueue(Customer c){
	pthread_mutex_lock(&lock);
	customer_count++;
	queue.push(c);
	pthread_mutex_unlock(&lock);
}

bool ThreadSafeQueue::lineEmpty() {
	pthread_mutex_lock(&lock);
	bool empty = customer_count == 0;
	pthread_mutex_unlock(&lock);
	return empty;
}

Customer ThreadSafeQueue::dequeue(){
	pthread_mutex_lock(&lock);

	if (!lineEmpty()) {
		customer_count--;
		Customer c = queue.front();
		queue.pop();
		pthread_mutex_unlock(&lock);
		return c;
	} else {
		pthread_mutex_unlock(&lock);
		return NULL;
	}
}

int ThreadSafeQueue::getCustomerCount(){
	return customer_count;
}
