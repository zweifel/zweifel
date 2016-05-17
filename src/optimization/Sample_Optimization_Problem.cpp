#include"Electric_Power_System_Scheduling.h"

Electric_Power_System_Scheduling::Electric_Power_System_Scheduling(char* data_filename, int problem_size, double minimum_value, double maximum_value)
{
	function_evaluations=0;
	this->problem_size= problem_size;
	this->maximum_value= maximum_size;
	this->minimum_value= minimum_size;
}

Electric_Power_System_Scheduling::~Electric_Power_System_Scheduling()
{

}

void Electric_Power_System_Scheduling::objectiveFunction(double* chromosome, double* response)
{
	function_evaluations++;

	double sum=0.0;
	for(int i=0;i<problem_size;++i)
	{
		//printf("%f ",chromosome[i]);
		sum+= chromosome[i]*chromosome[i];
	}

	response[0]= -sum;
}

void Electric_Power_System_Scheduling::printDetails(double* variables, double* return_value)
{

}

