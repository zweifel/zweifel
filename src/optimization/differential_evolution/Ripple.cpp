#include"Ripple.h"

Ripple::Ripple(int problem_size)
{
	this->problem_size= problem_size;
}

Ripple::~Ripple()
{

}


void Ripple::objectiveFunction(double* chromossome, double* response)
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
		response[0]= -9999;
	}

	//minimize function (negative)
	response[0]= -sum;
}

void Ripple::printDetails(double* variables, double* return_value)
{

}
