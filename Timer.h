/*
 * Time.h
 *
 *  Created on: Oct 10, 2016
 *      Author: rjd3756
 */

#ifndef TIME_H_
#define TIME_H_

#include <time.h>
#include <cstdlib>
#include <iostream>
#include "Constants.h"

class Timer {

public:
	void start();
	double timePassed();

};

#endif /* TIME_H_ */
