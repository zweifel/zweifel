
#ifndef GDE3_SUBPOPULATION_H
#define GDE3_SUBPOPULATION_H

#include"stdlib.h"
#include"stdio.h"
#include"string.h"
#include"Subpopulation.h"
#include"useful/useful_utils.h"
#include"math.h"
#include"../multiobjective_utils.h"

#include<vector>
#include<list>

using namespace std;

class GDE3_Subpopulation : public Subpopulation
{
public:
	GDE3_Subpopulation(int subpopulation_size, int number_of_problems, int problem_size);
	~GDE3_Subpopulation();

	int k;		//k nearest neighbors
	
	int number_of_problems;
	int max_subpopulation_size;
	int current_pop_size;

	int* index_array;
	double* diversity_dist;

	//temporary population (used as Cache)
	double** tmp_subpopulation;

	//implementing virtual functions
	void preProcess();
	bool weaker(double* a, double* b);
	void selectionPressure(double* new_individual, int parent_index);
	
	void storeSubpopulation(const char* filename);

	void reduceSubpopulation();

	//auxiliary functions
	
	bool isNondominated(double* a, double* b);
	int isWeakConstraintDominated(double* trial, double* parent);

};

#endif

