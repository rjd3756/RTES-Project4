/*
 * ThreadSafeQueue.cpp
 *
 *  Created on: Oct 5, 2016
 *      Author: rjd3756
 */
#include "ThreadSafeQueue.h"



ThreadSafeQueue::ThreadSafeQueue() {
	customer_count = 0;
}

void ThreadSafeQueue::Enqueue(Customer c){
	pthread_mutex_lock(&lock);
	customer_count++;
	queue.push(c);
	pthread_mutex_unlock(&lock);
}

bool ThreadSafeQueue::line_empty() {
	//std::cout << "Checking if line is empty. Customer count: " << customer_count << std::endl;
	pthread_mutex_lock(&lock);
	bool empty = customer_count == 0;
	pthread_mutex_unlock(&lock);
	return empty;
}

Customer ThreadSafeQueue::Dequeue(){
	//std::cout << "Dequeueing from line, customer count: " << customer_count << std::endl;
	pthread_mutex_lock(&lock);
	if (!line_empty()) {
		customer_count--;
		Customer c = queue.front();
		queue.pop();
		pthread_mutex_unlock(&lock);
		return c;
	} else {
		std::cout << "Line Empty - NULL Dequeue " << std::endl;
		pthread_mutex_unlock(&lock);
		return NULL;
	}
}
