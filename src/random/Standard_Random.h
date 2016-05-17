/***************************************************
 * Standard Random - Interface to the most common random() command
 *
 * Very fast when compared to other libraries, 
 * but with less randomness and may vary from system to system. 
 *
 * **************************************************/

#ifndef STANDARD_RANDOM_H
#define STANDARD_RANDOM_H

#include"Random.h"
#include<stdlib.h>

class Standard_Random: public Random
{
	private:
	

	public:
		
		Standard_Random(unsigned int seed);
		~Standard_Random();

		int uniform(int min, int max);
		double uniform(double min, double max);
		//return random result uniformly distributed between [0,1)
		double uniform();	
	
};

#endif
