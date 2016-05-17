///////////////////////////////////////////////////////////////
//	Scheduling of Electric Power Systems
//
//////////////////////////////////////////////////////////////

#ifndef ELECTRIC_POWER_SYSTEMS_H
#define ELECTRIC_POWER_SYSTEMS_H

#include"optimization/Optimization_Problem.h"
#include"math.h"
#include"stdio.h"
#include"stdlib.h"
#include"data.h"
//#include<limits.h>
//#include"iostream"



class Electric_Power_System_Scheduling: public Optimization_Problem
{
	public:
		Electric_Power_System_Scheduling(char* data_filename, int problem_size, double minimum_value, double maximum_value);
		~Electric_Power_System_Scheduling();
		
		//Optimization Problems's API variables
		//int function_evaluations;
		//int problem_size;
		//double maximum_value;
		//double minimum_value;

		//Optimization Problem's API 
		void objectiveFunction( double* variables, double* response);
		void printDetails( double* variables, double* return_value);

};

#endif
