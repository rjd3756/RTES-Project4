/*
 * Customer.cpp
 *
 *  Created on: Oct 5, 2016
 *      Author: rjd3756
 */

#include "Customer.h"


Customer::Customer(int idnum) {
	transactionTime = TIME_CONVERSION_MIN_TO_MICRO * (rand() % 330 + 30);
	id = idnum;
}
