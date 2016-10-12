/*
 * Timer.cpp
 *
 *  Created on: Oct 10, 2016
 *      Author: rjd3756
 */

#include "Timer.h"

Timer::Timer(){
	struct timespec start;
	timestart = start;
}

void Timer::start() {
	clock_gettime(CLOCK_REALTIME, &timestart);
	//std::cout << "Seconds: " << timestart.tv_sec << std::endl;
	//std::cout << "Nanoseconds: " << (timestart.tv_nsec) * TIME_CONVERSION_NANO_TO_SEC << std::endl;
}

double Timer::timePassed() {
	struct timespec timeend;
	clock_gettime(CLOCK_REALTIME, &timeend);

	//std::cout << "Seconds: " << timeend.tv_sec << std::endl;
	//std::cout << "Nanoseconds: " << (timeend.tv_nsec) * TIME_CONVERSION_NANO_TO_SEC << std::endl;

	double timeDiffSeconds = difftime(timeend.tv_sec, timestart.tv_sec);
	//std::cout << "Seconds: " << timeDiffSeconds << std::endl;
	long int timeDiffNanoSec = timeend.tv_nsec - timestart.tv_nsec;
	//std::cout << "Nanoseconds: " << timeDiffNanoSec << std::endl;
	//std::cout << "Total: " << timeDiffNanoSec * TIME_CONVERSION_NANO_TO_SEC + timeDiffSeconds << std::endl;
	return timeDiffNanoSec * TIME_CONVERSION_NANO_TO_SEC + timeDiffSeconds;
}

Timer::~Timer(){
}

