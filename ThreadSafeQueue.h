/*
 * ThreadSafeQueue.h
 *
 *  Created on: Oct 5, 2016
 *      Author: rjd3756
 */
#include <queue>

#ifndef THREADSAFEQUEUE_H_
#define THREADSAFEQUEUE_H_

class ThreadSafeQueue {
private:
	std::queue<Customer> queue;

public:
	ThreadSafeQueue();
	void Enqueue(Customer);
	Customer Dequeue();
};

#endif /* THREADSAFEQUEUE_H_ */
