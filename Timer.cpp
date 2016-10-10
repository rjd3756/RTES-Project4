/*
 * Timer.cpp
 *
 *  Created on: Oct 10, 2016
 *      Author: rjd3756
 */

#include "Timer.h"

struct timespec timestart;


void Timer::start() {
	clock_gettime(CLOCK_REALTIME, &timestart);
}

double Timer::stop() {
	struct timespec timeend;
	clock_gettime(CLOCK_REALTIME, &timeend);

	double timeDiffSeconds = difftime(timeend.tv_sec, timestart.tv_sec);
	std::cout << "Seconds: " << timeDiffSeconds << std::endl;
	long int timeDiffNanoSec = timeend.tv_nsec - timestart.tv_nsec;
	std::cout << "Nanoseconds: " << timeDiffNanoSec << std::endl;

	return timeDiffNanoSec * TIME_CONVERSION_NANO_TO_SEC + timeDiffSeconds;

}

