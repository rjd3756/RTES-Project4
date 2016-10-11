/*
 * Thread.cpp
 *
 *  Created on: Oct 3, 2016
 *      Author: rjd3756
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
	t->Teller::serve_customers();
}

void Teller::serve_customers() {
	while(1) {
		//std::cout << "Creating a new timer teller" << id << std::endl;
		Timer* timer = new Timer();
		//std::cout << "start timer teller" << id << std::endl;
		timer->start();
		while (bank->bank_empty()) {
			if (!bank->isBankOpen()) {
				return;
			}
			//std::cout << "Teller waiting for a customer... " << std::endl;
			pthread_cond_wait(&customerPresent, &lock);
		}
		Customer customer = bank->get_next_customer_in_line();
		//std::cout << "stop timer teller" << id << std::endl;
		double timeWaited = timer->timePassed();
		//std::cout << "Teller waited " << timeWaited << " for a customer." << std::endl;
		//std::cout << "Teller" << id << " takes person from line: " << customer.id << std::endl;
		usleep(customer.transactionTime);
		bank->TransactionComplete(id, customer.id, (customer.transactionTime / SIMULATION_TIME_CONVERSION_MIN_TO_MICRO), timeWaited);
	}
}

void Teller::CreateTellerThread(Teller* t){
	pthread_t thread;
	pthread_create(&thread, NULL, &Teller::start, (void*)t);
}
