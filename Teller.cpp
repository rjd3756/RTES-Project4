/*
 * Thread.cpp
 *
 *  Created on: Oct 3, 2016
 *      Author: rjd3756
 */

#include<Teller.h>

Teller::Teller(Bank* b){
	bank = b;
}

void* Teller::start(void* v)
{
	Teller* t = (Teller*)v;
	std::cout << "Teller Started" << std::endl;
	t->Teller::serve_customers();
}

void Teller::serve_customers() {
	std::cout << "Teller Execute" << std::endl;
	bank->TransactionComplete(0, 0);
}

void Teller::CreateTellerThread(Teller* t){
	pthread_t thread;
	pthread_create(&thread, NULL, &Teller::start, (void*)t);
}
