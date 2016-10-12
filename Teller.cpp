/*
 * Thread.cpp
 *
 *  Created on: Oct 3, 2016
 *      Author: Joey Bovio, RJ DiNardi
 */

#include<Teller.h>

Teller::Teller(Bank* b, int idnum, pthread_cond_t custPresent, pthread_mutex_t mutex){
	bank = b;
	id = idnum;
	customerPresent = custPresent;
	lock = mutex;
}

void* Teller::start(void* v)
{
	Teller* t = (Teller*)v;
	std::cout << "Teller Thread Started" << std::endl;
	t->Teller::serveCustomers();
}

void Teller::serveCustomers() {
	while(1) {
		Timer* timer = new Timer();
		timer->start();

		//look to see if the line is empty
		while (bank->bankEmpty()) {
			//look to see if the bank is closed
			if (!bank->isBankOpen()) {
				std::cout << "Teller goes home" << std::endl;
				return;
			}
			pthread_cond_wait(&customerPresent, &lock);
		}

		//get the next customer in line
		Customer customer = bank->getNextCustomerInLine();
		double timeWaited = timer->timePassed();
		usleep(customer.transactionTime);

		bank->transactionComplete(id, customer.id, customer.transactionTime * MICROSECONDS_TO_SECONDS, timeWaited, customer.timeSpentInQueue);
	}
}

void Teller::createTellerThread(Teller* t){
	pthread_t thread;
	pthread_create(&thread, NULL, &Teller::start, (void*)t);
}
