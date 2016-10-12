/*
 * Timer.cpp
 *
 *  Created on: Oct 10, 2016
 *      Author: Joey Bovio, RJ DiNardi
 */

#include "Timer.h"

Timer::Timer(){
	struct timespec start;
	timestart = start;
}

void Timer::start() {
	clock_gettime(CLOCK_REALTIME, &timestart);
}

double Timer::timePassed() {
	struct timespec timeend;
	clock_gettime(CLOCK_REALTIME, &timeend);

	double timeDiffSeconds = difftime(timeend.tv_sec, timestart.tv_sec);
	long int timeDiffNanoSec = timeend.tv_nsec - timestart.tv_nsec;

	return timeDiffNanoSec * TIME_CONVERSION_NANO_TO_SEC + timeDiffSeconds;
}

Timer::~Timer(){

}

