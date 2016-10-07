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
	int Create();
	Teller();
private:
	static void* start(void*);
};

#endif /* THREAD_H_ */
