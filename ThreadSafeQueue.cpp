/*
 * ThreadSafeQueue.cpp
 *
 *  Created on: Oct 5, 2016
 *      Author: rjd3756
 */
#include "ThreadSafeQueue.h"



ThreadSafeQueue::ThreadSafeQueue() {
	//std::queue<Customer> queue;
}

void ThreadSafeQueue::Enqueue(Customer c){
	pthread_mutex_lock(&lock);
	customer_count++;
	queue.push(c);
	pthread_mutex_unlock(&lock);
}

bool ThreadSafeQueue::line_empty() {
	return (customer_count == 0);
}

Customer ThreadSafeQueue::Dequeue(){
	pthread_mutex_lock(&lock);
	customer_count--;
	Customer c = queue.front();
	queue.pop();
	pthread_mutex_unlock(&lock);
	return c;
}
