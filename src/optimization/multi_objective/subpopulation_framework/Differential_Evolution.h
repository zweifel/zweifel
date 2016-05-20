#ifndef DIFFERENTIAL_EVOLUTION_H
#define DIFFERENTIAL_EVOLUTION_H

#include<stdlib.h>
#include<stdio.h>
#include"optimization/Optimization_Problem.h"
#include"common.h"
#include"math.h"
#include"useful/useful_utils.h"
#include"useful/useful_plots.h"
#include"optimization/Optimization_Method.h"
#include"random/Random.h"
#include"Classic_Subpopulation.h"
//#include"Average_Subpopulation.h"
//#include"Pareto_Subpopulation.h"
#include"GDE3_Subpopulation.h"
#include"Novelty_Subpopulation.h"

/*
 Subpopulation Table
Array concatenated of:
 -variables
 -fitness values
 -other characteristics
 ----------------- 
 | | | | | | | | | 
 | | | | | | | | | 
 | | | | | | | | | 
 | | | | | | | | | 
 | | | | | | | | | 
 ----------------- 
 | | | | | | | | | 
 | | | | | | | | | 
 | | | | | | | | | 
 | | | | | | | | | 
 | | | | | | | | | 
 -----------------


Individual:
 ___________________________________
|  variables | fitnesses | overhead |  
|____________|___________|__________|
*/

class Differential_Evolution: public Optimization_Method
{
	public:
		Differential_Evolution(int max_generations, int population_size, int subpopulation_size, double max_limit, double min_limit, float F, float CR, Random* random);
		~Differential_Evolution();

		int generation;
		int max_generations;

		int number_of_subpopulations; 	//equal to the number_of_"objectives" (new objectives), since each subpop has its own objective
		int number_of_problems;

		int population_size;
		int subpopulation_size;

		double max_limit;
		double min_limit;
		double F;
		double CR;
		double S;
		
		FILE* new_fp;
		FILE* new_fp2;

		Random* random;

		Optimization_Problem* problem;

		//double** population;
		Subpopulation** population;

		//void generateRandomIndividual(int individual);
		void generateRandomIndividual();
		double generateRandomVariable(int variable);
		void allocatePopulations();

		//operators
		void mutationOperator(int subpopulation);
		void crossoverOperator(int subpop, int individual);

		double* trial_vector;
		//double* ind;

		void printParameters();
		void storeSolutions(const char* filename);
		
		//int getBestIndividual();
		int newGeneration();

			
		//implement virtual methods
		double optimize(Optimization_Problem* optimization_problem, int number_of_problems, double** solution);
		double optimizeDebug(Optimization_Problem* optimization_problem, int number_of_problems, double** solution);
		
		//debug
		double* tmp;
};

#endif
