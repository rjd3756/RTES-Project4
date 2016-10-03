/*
 * Banker.cpp
 *
 *  Created on: Oct 3, 2016
 *      Author: rjd3756
 */

#include "Thread.cpp"

class Banker: Thread{
public:
	Banker();
private:
	void *start(){
		return 0;
	}

};

Banker::Banker(){

}
