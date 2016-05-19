

#include"Average_Subpopulation.h"


Average_Subpopulation::Average_Subpopulation(int subpopulation_size, int number_of_problems, int problem_size)
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

	printf("avg\n");
}
	
//Is individual a weaker than individual b?
bool Average_Subpopulation::weaker(double* a, double* b)
{
	int i;
	double avg_sum_a=0.0;
	double avg_sum_b=0.0;

	for(i=0; i<number_of_problems; ++i)
	{
		avg_sum_a+= a[problem_size + i];
		avg_sum_b+= b[problem_size + i];
	}
	

	return avg_sum_a < avg_sum_b;
}


void Average_Subpopulation::preProcess()
{

}

