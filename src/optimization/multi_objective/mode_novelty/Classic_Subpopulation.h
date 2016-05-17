
#ifndef CLASSIC_SUBPOPULATION_H
#define CLASSIC_SUBPOPULATION_H

#include"stdlib.h"
#include"stdio.h"
#include"string.h"
#include"Subpopulation.h"
#include"useful/useful_utils.h"
#include"math.h"

class Classic_Subpopulation : public Subpopulation
{
public:
	Classic_Subpopulation(int objective_index, int subpopulation_size, int number_of_problems, int problem_size);
	~Classic_Subpopulation();
	
	bool weaker(double* a, double* b);
	
	void selectionPressure(double* new_individual, int parent_index);

	void preProcess();
	
};

#endif

