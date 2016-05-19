
#ifndef SUBPOPULATION_PRIORITYH
#define SUBPOPULATION_PRIORITYH

#include"stdlib.h"
#include"stdio.h"
#include"string.h"
#include"useful/useful_utils.h"
#include"useful/read_csv.h"
#include"math.h"

class Subpopulation_Priority
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

	virtual bool weaker(double* a, double* b)=0;
	void insert(double* individual);
	void testInsert(double* individual);

	void ascendHeap(int index);
	void descendHeap(int index);

	void printSubpopulation();
	void storeSubpopulation(const char* filename);
};

#endif

