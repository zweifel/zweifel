
#ifndef NOVELTY_SUBPOPULATION_H
#define NOVELTY_SUBPOPULATION_H

#include"stdlib.h"
#include"stdio.h"
#include"string.h"
#include"Subpopulation.h"
#include"useful/useful_utils.h"
#include"math.h"

#include<vector>
#include<list>

using namespace std;

typedef struct _paar
{
	int index;
	double value;
}paar;

static double* novelty_array;

static int novelty_comparison(const void* p1, const void* p2)
{
	const int *a = (const int*)p1;
	const int *b = (const int*)p2;

	if(novelty_array[*a]<novelty_array[*b])
	{
		return 1;		
	}
	else
	{
		return -1;
	}

	return 0;
}

static int double_comparison(const void *a, const void *b)
{
	if( *(double*)a - *(double*)b >0)
	{
		return 1;
	}
	else
	{
		return -1;
	}
}

static int paar_comparison(const void *p1, const void *p2)
{
	
	const paar *a = (const paar*)p1;
	const paar *b = (const paar*)p2;

	double v1= (*a).value;
	double v2= (*b).value;

	if( v1 - v2 >0)
	{
		return 1;
	}
	else
	{
		return -1;
	}
}


class Novelty_Subpopulation : public Subpopulation
{
public:
	Novelty_Subpopulation(int subpopulation_size, int number_of_problems, int problem_size);
	~Novelty_Subpopulation();

	void addIndividual(double* ind);

	int k;		//k nearest neighbors
	
	int generation;

	int number_of_problems;

	int archive_size_limit;

	bool weaker(double* a, double* b);
	bool isNondominated(double* a, double* b);
	void storeSubpopulation(const char* filename);
	void createNoveltyBasedSubpopulation();
	void createCrowdingdistanceBasedSubpopulation();

	void preProcess();
	void createFronts();
	void joinNondominated();

	list<double*> novelty_sorted;
	vector<double*> all_fronts;

	vector<double*> front1;
	vector<double*> front2;
	vector<double*> front3;
	vector<double*> front4;
	vector<double*> front5;
	list<double*> free_arrays;

	//auxiliary functions
	
	void createFront(vector<double*>& front);
	void copyFront(vector<double*>& front);
};

#endif

