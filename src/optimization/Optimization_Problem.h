
#ifndef OPTIMIZATION_PROBLEM_H
#define OPTIMIZATION_PROBLEM_H

#include"common.h"

class Optimization_Problem
{
	public:
		
		virtual ~Optimization_Problem(){};

		int function_evaluations;
		int problem_size;
		double maximum_value;
		double minimum_value;

		//pass the variables and the vector to be used as return value
		//in the case of single optimization (multi-objective optimization), 
		//the return_value will be the size of one variable (the size of the number of objectives)
		//
		//The return_value passed as parameter, must be already allocated
		virtual void objectiveFunction(double* variables, double* return_value) = 0;

		//the same as above but very verbose
		virtual void printDetails(double* variables, double* return_value) = 0;

};

/*
Optimization_Problem::~Optimization_Problem()
{

}*/

#endif
