
#ifndef PARETO_SUBPOPULATION_H
#define PARETO_SUBPOPULATION_H

#include"stdlib.h"
#include"stdio.h"
#include"string.h"
#include"Subpopulation.h"
#include"useful/useful_utils.h"
#include"math.h"

class Pareto_Subpopulation : public Subpopulation
{
public:
	Pareto_Subpopulation(int subpopulation_size, int number_of_problems, int problem_size);
	~Pareto_Subpopulation();
	
	int number_of_problems;

	bool weaker(double* a, double* b);

	void preProcess();

};

#endif

