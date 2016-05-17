

#ifndef OPTIMIZATION_METHOD_H
#define OPTIMIZATION_METHOD_H

#include"common.h"
#include"Optimization_Problem.h"

class Optimization_Method
{
	public:

		virtual ~Optimization_Method(){};

		//return the maximum found
		//and set the solution to the vector solution found.
		virtual double optimize(Optimization_Problem* problem, int number_of_objectives, double** solution) = 0;
		//with more Debug output
		virtual double optimizeDebug(Optimization_Problem* problem, int number_of_objectives, double** solution) = 0;

};
		
/*
Optimization_Method::~Optimization_Method()
{

}*/

#endif
