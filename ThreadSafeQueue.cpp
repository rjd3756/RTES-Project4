/*
 * ThreadSafeQueue.cpp
 *
 *  Created on: Oct 5, 2016
 *      Author: rjd3756
 */

#include "ThreadSafeQueue.h"

ThreadSafeQueue::ThreadSafeQueue() {
	std::queue<Customer> q;
	this.queue = q;
}

void ThreadSafeQueue::Enqueue(Customer c){

}

Customer ThreadSafeQueue::Dequeue(){

}
