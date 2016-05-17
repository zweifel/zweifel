

#ifndef GENERIC_PROBLEM_H
#define GENERIC_PROBLEM_H

#include"optimization/Optimization_Problem.h"
#include"math.h"

class Generic_Problem: public Optimization_Problem
{
	public:

		Generic_Problem( double(*fitnessfunction)(double*), int problem_size);
		~Generic_Problem();

		double (*fitness_function)(double*);

		void objectiveFunction(double* variables, double* response);
		void printDetails(double* variables, double* return_value);

};

#endif
