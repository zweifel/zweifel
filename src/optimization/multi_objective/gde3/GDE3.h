#ifndef GDE3_H
#define GDE3_H

#include<stdlib.h>
#include<stdio.h>
#include"optimization/Optimization_Problem.h"
#include"common.h"
#include"math.h"
#include"useful/useful_utils.h"
#include"useful/read_csv.h"
#include"useful/useful_plots.h"
#include"optimization/Optimization_Method.h"
#include"random/Random.h"
#include"../multiobjective_utils.h"

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

class GDE3: public Optimization_Method
{
	public:
		GDE3(int max_generations, int population_size, double max_limit, double min_limit, float F, float CR, Random* random);
		~GDE3();

		int generation;
		int max_generations;

		FILE* new_fp;
		FILE* new_fp2;

		//int number_of_subpopulations; 	//equal to the number_of_"objectives" (new objectives), since each subpop has its own objective
		int number_of_problems;

		bool isNondominated(double* a, double* b);
		int isWeakConstraintDominated(double* trial, double* parent);

		int individual_size;
		int max_population_size;
		int population_size;
		int current_pop_size;

		double max_limit;
		double min_limit;
		double F;
		double CR;
		
		Random* random;

		Optimization_Problem* problem;

		int* index_array;
		double* diversity_dist;

		double** population;
		double** tmp_population;
		//Subpopulation** population;

		//void generateRandomIndividual(int individual);
		void generateRandomIndividual();
		double generateRandomVariable(int variable);
		void allocatePopulations();

		void useCrowdingdistance();

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
