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

class Differential_Evolution: public Optimization_Method
{
	public:
		Differential_Evolution(int max_generations, int population_size, double max_limit, double min_limit, float F, float CR, Random* random);
		~Differential_Evolution();

		int generation;
		int max_generations;

		int population_size;

		double max_limit;
		double min_limit;
		double F;
		double CR;
		
		Random* random;

		Optimization_Problem* problem;

		double** population;

		void generateRandomIndividual(int individual);
		void generatePartiallyRandomIndividual(int individual);
		double generateRandomVariable(int variable);
		
		bool problem_previously_defined;
		int allocated_problem_size;
		
		void allocatePopulations();
		void allocateProblemMemory();
		void freeProblemMemory();
		void reallocateProblemMemory();

		//operators
		void mutationOperator(int individual);
		void crossoverOperator(int individual);

		double* trial_vector;

		void printParameters();
		
		int getBestIndividual();
		int newGeneration();

		bool keep_previous_individuals;
		int last_problem_size;
			
		//implement virtual methods
		double optimize(Optimization_Problem* optimization_problem, int number_of_problems, double** solution);
		double optimizeDebug(Optimization_Problem* optimization_problem, int number_of_problems, double** solution);
		//API - other important functions 
		void keepPreviousIndividuals();

		//debug
		double* fitness;
};

#endif
