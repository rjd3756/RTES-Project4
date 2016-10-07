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

int Teller::Create()
	{
		 pthread_t thread;
		 pthread_create(&thread, NULL, &start, NULL);
		 std::cout << thread << std::endl;
		 return 0;
	}

void* Teller::start(void*){
	std::cout << "thread ran" << std::endl;
}
