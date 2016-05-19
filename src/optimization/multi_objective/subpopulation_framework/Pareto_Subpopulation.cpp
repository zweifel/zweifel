

#include"Pareto_Subpopulation.h"


Pareto_Subpopulation::Pareto_Subpopulation(int subpopulation_size, int number_of_problems, int problem_size)
{
	this->problem_size= problem_size;
	this->subpopulation_size= subpopulation_size;

	available_index=0;
	individual_size=number_of_problems + problem_size;
	this->number_of_problems= number_of_problems;

	subpopulation= (double**)malloc(sizeof(double*)*subpopulation_size);
	for(int i=0;i<subpopulation_size; ++i)
	{	
		subpopulation[i]= (double*)malloc(sizeof(double)*(individual_size));		
	}

	printf("pareto\n");
}
	
//Is individual a weaker than individual b?
bool Pareto_Subpopulation::weaker(double* a, double* b)
{
	int i;

	for(i=0; i<number_of_problems; ++i)
	{
		if(a[problem_size + i] <  b[problem_size + i])
		{
			return true;
		}
	}

	return false;
}

void Pareto_Subpopulation::preProcess()
{

}

