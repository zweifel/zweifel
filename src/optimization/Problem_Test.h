/****************************************************************************
 *
 * 	Class created to Test the Optimization Problem
 *
 ****************************************************************************/

#ifndef PROBLEM_TEST_H
#define PROBLEM_TEST_H


#include<stdlib.h>
#include<stdio.h>
#include"optimization/Optimization_Problem.h"
#include"math.h"
#include"optimization/Optimization_Method.h"
#include"random/Random.h"

class Problem_Test: public Optimization_Method
{
	public:
		Problem_Test();
		~Problem_Test();

		//implement virtual methods
		double optimize(Optimization_Problem* optimization_problem, int number_of_problems, double** solution);
		double optimizeDebug(Optimization_Problem* optimization_problem, int number_of_problems, double** solution);

		void testSolution(double* chromosome, Optimization_Problem* problem);
};

#endif
