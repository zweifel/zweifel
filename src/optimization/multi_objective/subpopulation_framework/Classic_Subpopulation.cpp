
#include"Classic_Subpopulation.h"


Classic_Subpopulation::Classic_Subpopulation(int objective_index, int subpopulation_size, int number_of_problems, int problem_size)
{
	this->problem_size= problem_size;
	this->objective= objective_index;
	this->subpopulation_size= subpopulation_size;

	available_index=0;
	individual_size=number_of_problems + problem_size;

	subpopulation= (double**)malloc(sizeof(double*)*subpopulation_size);
	for(int i=0;i<subpopulation_size; ++i)
	{	
		subpopulation[i]= (double*)malloc(sizeof(double)*(individual_size));		
	}
	
	printf("Classic Subpopulation initialized, objective %d\n",objective_index);
}
	
//Is individual a weaker than individual b?
bool Classic_Subpopulation::weaker(double* a, double* b)
{
	return a[problem_size + objective] < b[problem_size + objective];
}

void Classic_Subpopulation::preProcess()
{

}
	
void Classic_Subpopulation::selectionPressure(double* new_individual, int parent_index)
{

	if(!weaker(new_individual, subpopulation[parent_index]))
	{
		memcpy(subpopulation[parent_index], new_individual, individual_size*sizeof(double));
	}
	
}

