/*
 * Thread.h
 *
 *  Created on: Oct 5, 2016
 *      Author: rjd3756
 */

#ifndef THREAD_H_
#define THREAD_H_

class Teller{
public:
	void start();
	Teller();
private:
	static void* serve_customers(void*);
};

#endif /* THREAD_H_ */
