
#ifndef SUBPOPULATION_H
#define SUBPOPULATION_H

#include"stdlib.h"
#include"stdio.h"
#include"string.h"
#include"useful/useful_utils.h"
#include"useful/read_csv.h"
#include"math.h"

class Subpopulation
{
public:
	//Subpopulation(int objective_index, int subpopulation_size, int number_of_objectives, int problem_size);
	//~Classic_Subpopulation();
	
	int objective;
	int problem_size;

	//population variables
	double** subpopulation;
	int subpopulation_size;
	int available_index;
	int number_of_objectives;
	int individual_size;

	virtual void preProcess()=0;	//called at the beginning of each generation

	virtual bool weaker(double* a, double* b)=0;
	virtual void selectionPressure(double* new_individual, int parent_index)=0;

	virtual void insert(double* individual);
	void testInsert(double* individual);

	void ascendHeap(int index);
	void descendHeap(int index);

	void printSubpopulation();
	virtual void storeSubpopulation(const char* filename);
};

#endif

