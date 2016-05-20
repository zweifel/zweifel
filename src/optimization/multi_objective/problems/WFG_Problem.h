
#ifndef WFG_PROBLEM_H
#define WFG_PROBLEM_H

#include"optimization/Optimization_Problem.h"
#include "Toolkit/ExampleProblems.h"
#include "Toolkit/TransFunctions.h"

#include<vector>
#include"stdio.h"
#include"stdlib.h"
#include"string.h"

using namespace std;

enum{WFG1,WFG2,WFG3,WFG4,WFG5,WFG6,WFG7,WFG8,WFG9};

using namespace WFG::Toolkit;
using namespace WFG::Toolkit::Examples;

class WFG_Problem: public Optimization_Problem
{
	public:

		WFG_Problem(int problem_type, int position_parameters, int distance_parameters, int number_of_problems);
		~WFG_Problem();

		int problem_type;
		int number_of_problems;

		int k;
		int l;

		void objectiveFunction(double* variables, double* result);
		void printDetails(double* variables, double* result);

};

#endif
