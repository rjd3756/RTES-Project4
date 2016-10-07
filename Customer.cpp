/*
 * Customer.cpp
 *
 *  Created on: Oct 5, 2016
 *      Author: rjd3756
 */

#include "Customer.h"

const unsigned int SEED = 7;

Customer::Customer() {
	int transactionTimeRequired = rand() % 330 + 30;
}
