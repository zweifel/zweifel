#ifndef GENETIC_H
#define GENETIC_H

#include"time.h"
#include<stdlib.h>
#include<stdio.h>
#include"optimization/Optimization_Problem.h"
#include"common.h"
#include"math.h"
#include"random.hpp"
#include"useful/useful_utils.h"
#include"useful/useful_plots.h"
#include"optimization/Optimization_Method.h"

class Goldberg_GA: public Optimization_Method
{
	public:
		Goldberg_GA(int population_size, double max_limit, double min_limit, float selection_pressure, float crossing_over_probability, float mutation_rate);
		~Goldberg_GA();

		float selection_pressure;
		float crossing_over_probability;
		float mutation_rate;
		double max_limit;
		double min_limit;
		int generation;

		int population_size;
		int selected_population_size;
		randomG random;

		Optimization_Problem* problem;

		static bool initialized_seed;

		double** population;
		double** selected_population;

		void generateRandomIndividual(int individual);
		double generateRandomVariable(int variable);
		void generateMutatedVariable(int individual, int variable);
		void allocatePopulations();
		int simple_tournament(int max_participants, int population_size);
		bool isGreater(double new_fitness, double best_fitness);
		bool isLower(double new_fitness, double best_fitness);

		void printParameters();
		
		int getBestIndividual();
		int newGeneration();
			
		//implement virtual methods
		double optimize(Optimization_Problem** optimization_problem, int number_of_problems, double** solution);
		double optimizeDebug(Optimization_Problem** optimization_problem, int number_of_problems,double** solution);
		
		//debug
		double* tmp;
};

#endif
