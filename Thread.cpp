/*
 * Thread.cpp
 *
 *  Created on: Oct 3, 2016
 *      Author: rjd3756
 */

#include<pthread.h>
#include<iostream>


class Thread{


public:
	int Create()
	{
		 pthread_t thread;
		 pthread_create(&thread, NULL, startRoutine, this);
		 std::cout << thread << std::endl;
		 return 0;
	}

protected:
	virtual void *start() = 0;

	private:
		static void *startRoutine(void *p)
		{
				Thread *pThis = (Thread *)p;
				return pThis->start();
		}
};
