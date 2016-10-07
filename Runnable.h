/*
 * Runnable.h
 *
 *  Created on: Oct 7, 2016
 *      Author: rjd3756
 */

#ifndef RUNNABLE_H_
#define RUNNABLE_H_

class Runnable {
public:
	static void create_thread(Runnable *runnable_ref);
	virtual void start();

private:
	static void *call_start(void* runnable);
};

#endif /* RUNNABLE_H_ */
