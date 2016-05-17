#include"Generic_Problem.h"

Generic_Problem::Generic_Problem( double(*fitnessfunction)(double*), int problem_size)
{
	this->problem_size= problem_size;

	this->fitness_function= fitnessfunction;	

	function_evaluations=0;
}

Generic_Problem::~Generic_Problem()
{

}


void Generic_Problem::objectiveFunction(double* chromossome, double* response)
{
	function_evaluations++;
	
	double fitness= fitness_function(chromossome);
	
	//minimize function (negative)
	response[0]= -fitness;	
}

void Generic_Problem::printDetails(double* variables, double* return_value)
{

}
