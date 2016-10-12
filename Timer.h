/*
 * Time.h
 *
 *  Created on: Oct 10, 2016
 *      Author: Joey Bovio, RJ DiNardi
 */

#ifndef TIME_H_
#define TIME_H_

#include <time.h>
#include "Constants.h"

class Timer {

public:
	Timer();
	void start();
	double timePassed();
	~Timer();

private:
	timespec timestart;
};

#endif /* TIME_H_ */
