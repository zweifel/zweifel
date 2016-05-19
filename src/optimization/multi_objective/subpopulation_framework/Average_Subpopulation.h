
#ifndef AVERAGE_SUBPOPULATION_H
#define AVERAGE_SUBPOPULATION_H

#include"stdlib.h"
#include"stdio.h"
#include"string.h"
#include"Subpopulation.h"
#include"useful/useful_utils.h"
#include"math.h"

class Average_Subpopulation : public Subpopulation
{
public:
	Average_Subpopulation(int subpopulation_size, int number_of_problems, int problem_size);
	~Average_Subpopulation();
	
	int number_of_problems;

	bool weaker(double* a, double* b);

	void preProcess();
	
};

#endif

