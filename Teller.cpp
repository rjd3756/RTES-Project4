/*
 * Thread.cpp
 *
 *  Created on: Oct 3, 2016
 *      Author: rjd3756
 */

#include<pthread.h>
#include<iostream>
#include<Teller.h>

Teller::Teller(){

}

void Teller::start()
	{
		 pthread_t thread;
		 pthread_create(&thread, NULL, &serve_customers, NULL);
		 std::cout << thread << std::endl;
	}

void* Teller::serve_customers(void*){

}
