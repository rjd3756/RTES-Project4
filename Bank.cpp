/*
 * Bank.cpp
 *
 *  Created on: Oct 5, 2016
 *      Author: rjd3756
 */

#include "Bank.h"

//have to declare these here as well so that there is space allocated at runtime for them
ThreadSafeQueue Bank::customer_line;
Teller Bank::tellers[NUMBER_OF_TELLERS];

Bank::Bank() {
	customer_line = ThreadSafeQueue::ThreadSafeQueue();
}

void Bank::start(){
	std::cout << "Bank Started" << std::endl;
}

void* Bank::execute(void*) {
	//hire tellers
	for(int i = 0; i < NUMBER_OF_TELLERS; ++i){
		tellers[i] = Teller::Teller();
	}

	//(9 am) begin servicing customers today
	open();


	return 0;
}

void Bank::open(){
	for(int i = 0; i < NUMBER_OF_TELLERS; ++i){
		tellers[i].start();
	}
}

void Bank::customer_enter() {


}

Bank::~Bank() {
	pthread_cancel(thread_id);
}
