/*
 * Customer.h
 *
 *  Created on: Oct 5, 2016
 *      Author: rjd3756
 */
#include <stdlib.h>
#include "Constants.h"

#ifndef CUSTOMER_H_
#define CUSTOMER_H_

class Customer {
public:
	Customer(int idnum);
	int id;
	int transactionTime;
};

#endif /* CUSTOMER_H_ */
