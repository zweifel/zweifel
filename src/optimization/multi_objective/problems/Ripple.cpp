#include"Ripple.h"

Ripple::Ripple(int problem_size)
{
	this->problem_size= problem_size;
}

Ripple::~Ripple()
{

}


void Ripple::objectiveFunction(double* chromossome, double* result)
{
	int i;
	double sum= 0.0;
	
	for(i=0; i< problem_size ;++i)
	{
		sum+= chromossome[i]*chromossome[i];
	}
	sum= sin(sum);

	sum= sqrt(sum);

	if(isnan(sum))
	{
		result[0]= -9999;
	}

	//minimize function (negative)
	result[0]= -sum;
}
		
void Ripple::printDetails(double* variables, double* result)
{
	objectiveFunction(variables, result);
}
