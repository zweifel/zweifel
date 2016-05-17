
#ifndef NOVELTY_SUBPOPULATION_H
#define NOVELTY_SUBPOPULATION_H

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

class Novelty_Subpopulation : public Subpopulation
{
public:
	Novelty_Subpopulation(int subpopulation_size, int number_of_problems, int problem_size);
	~Novelty_Subpopulation();

	void addIndividual(double* ind);

	int k;		//k nearest neighbors
	
	int generation;

	int number_of_problems;

	double** archive;
	int archive_size;
	int max_archive_size;
	
	double* nearest_neighbors_distance;
	int* index_array;
	int novelty_rejected_counter;
	int generation_counter;
	int last_individual_generation;
	double novelty_threshold;

	//implementing virtual functions
	void preProcess();
	bool weaker(double* a, double* b);
	void selectionPressure(double* new_individual, int parent_index);
	
	void storeSubpopulation(const char* filename);

};

#endif

