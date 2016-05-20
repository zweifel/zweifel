

#ifndef RIPPLE_H
#define RIPPLE_H

#include"optimization/Optimization_Problem.h"
#include"math.h"

class Ripple: public Optimization_Problem
{
	public:

		Ripple( int problem_size);
		~Ripple();

		void objectiveFunction(double* variables, double* result);
		void printDetails(double* variables, double* result);

};

#endif
