
#include"Subpopulation_Framework.h"

// random 	The random variable should be initialized before
// F		Should be between [0,2]	
// CR		Should be between [0,1]	
Subpopulation_Framework::Subpopulation_Framework(int max_generations, int population_size, int subpopulation_size, double max_limit, double min_limit, float F, float CR, Random* random)
{
	generation=1;
	this->max_generations= max_generations;
	
	this->population_size= population_size;
	this->subpopulation_size= subpopulation_size;

	this->max_limit= max_limit;
	this->min_limit= min_limit;

	this->random=random;

	tmp=(double*)malloc(sizeof(double)*population_size);


	this->F= F;
	this->CR= CR;
	
	printParameters();	
	
	
}

Subpopulation_Framework::~Subpopulation_Framework()
{
	int i;

	for(i=0;i<population_size;++i)
	{	
		free(population[i]);
	}
	free(population);
		
}

void Subpopulation_Framework::mutationOperator(int subpopulation)
{
	int i;

	double* r1;
	double* r2;
	double* r3;
	
	//choosing 3 individuals from any subpopulations randomly
	
	int random_subpop;
	int random_ind;
	
	//S= random->uniform(0.0,1.0);
	S=0.0;

	if(random->uniform(0.0,1.0)>S)
	{
		random_subpop= random->uniform(0,number_of_subpopulations-1);
		random_ind= random->uniform(0,population[random_subpop]->available_index-1);

		r1= population[random_subpop]->subpopulation[random_ind];	
		
		random_subpop= random->uniform(0,number_of_subpopulations-1);
		random_ind= random->uniform(0,population[random_subpop]->available_index-1);
		
		r2= population[random_subpop]->subpopulation[random_ind];	
		
		random_subpop= random->uniform(0,number_of_subpopulations-1);
		random_ind= random->uniform(0,population[random_subpop]->available_index-1);
		
		r3= population[random_subpop]->subpopulation[random_ind];	
	}
	else
	{
		random_ind= random->uniform(0,population[subpopulation]->available_index-1);

		r1= population[subpopulation]->subpopulation[random_ind];	
		
		random_ind= random->uniform(0,population[subpopulation]->available_index-1);
		
		r2= population[subpopulation]->subpopulation[random_ind];	
		
		random_ind= random->uniform(0,population[subpopulation]->available_index-1);
		
		r3= population[subpopulation]->subpopulation[random_ind];	

	}

	for(i=0;i<problem->problem_size;++i)
	{
		//F=random->uniform(0.0,2.0);
		trial_vector[i]= r1[i] + F*(r2[i] - r3[i]);
	
	}
/*
	if(population_size >= 4)
	{
		int r1, r2, r3; //index of individuals

		r1= random->uniform(0,population_size-1);

		while(r1 == individual)
		{
			r1= random->uniform(0,population_size-1);
		}
		
		r2= random->uniform(0,population_size-1);

		while(r2== individual)
		{
			r2= random->uniform(0,population_size-1);
		}
		
		r3= random->uniform(0,population_size-1);

		while(r3== individual)
		{
			r3= random->uniform(0,population_size-1);
		}

		for(i=0;i<problem->problem_size;++i)
		{
			F=random->uniform(0.0,1.0);
			trial_vector[i]= population[r1][i] + F*(population[r2][i] - population[r3][i]);
		}
	}
	else
	{
		int r1, r2, r3; //index of individuals

		r1= random->uniform(0,population_size-1);
		r2= random->uniform(0,population_size-1);
		r3= random->uniform(0,population_size-1);

		for(i=0;i<problem->problem_size;++i)
		{
			//F=random->uniform(0.0,1.0);
			trial_vector[i]= population[r1][i] + F*(population[r2][i] - population[r3][i]);
		
		}
	}

	*/
}

void Subpopulation_Framework::crossoverOperator(int subpop, int individual)
{
	int i;
	
	//choose a random index, to ensure that at least this will be inserted in the trial_vector
	int random_index= random->uniform(0,problem->problem_size-1);
	
	//choose a random individual
	//int random_subpop= random->uniform(0,number_of_subpopulations-1);
	//int random_ind= random->uniform(0,population[random_subpop]->available_index-1);

	double* r1= population[subpop]->subpopulation[individual];	

	/*
	if(random->uniform()>0.5)
	{
		CR=0.9;
	}
	else
	{
		CR=0.1;
	}
	CR=random->uniform(0.1,0.9);
	*/
	//CR=random->uniform(0.1,0.9);
	
		
	for(i=0;i<problem->problem_size;++i)
	{

		if(random_index != i && random->uniform() > CR)
		{
			trial_vector[i]= r1[i];
		}
		else
		{
		//	trial_vector[i]= mutation_vector[i];
//			if(trial_vector[i]>max_limit || trial_vector[i]<min_limit)
//			{
//				trial_vector[i]= generateRandomVariable(i);
//			}
		}
	}
}

void Subpopulation_Framework::printParameters()
{
	printf("population size %d\n",population_size);
	printf("max_limit %f\n",max_limit);
	printf("min_limit %f\n",min_limit);
	printf("F %f\n", F);
	printf("CR %f\n", CR);
}

double Subpopulation_Framework::optimize(Optimization_Problem* optimization_problem, int number_of_problems, double** solution)
{
	int i,j,k;

	if(number_of_problems==1)
	{
		printf("ERROR: MODE can only solve multiple problems at a time, it is not single-objective\n");
		exit(1);
	}
	
	/////////////// Allocating memory////////////////////

	problem= optimization_problem;
	this->number_of_problems= number_of_problems;
	
	//trial_vector=(double*)malloc(sizeof(double)*problem->problem_size);
	trial_vector = (double*)malloc(sizeof(double)*(problem->problem_size + number_of_problems));
	
	//allocating 
	allocatePopulations();

	//allocate individual (used for generating new individuals)
	//ind = (double*)malloc(sizeof(double)*(problem->problem_size + number_of_problems));


	///////////////// initialization generate random population //////////////////////
	
	/*
	for(i=0;i<population_size;++i)
	{	
		generateRandomIndividual();
		
		//append objective to the individual
		problem->objectiveFunction(trial_vector, (trial_vector + problem->problem_size));

		//problem->objectiveFunction(population[i], &tmp[i]);
		for(j=0;j<number_of_subpopulations;++j)
		{
			population[j]->testInsert(trial_vector);
		}
	}
	*/

	for(i=0;i<number_of_subpopulations;++i)
	{
		for(j=0; j<(population[i])->subpopulation_size;++j)
		{
			for(k=0; k<problem->problem_size; ++k)
			{
				(population[i])->subpopulation[j][k]= generateRandomVariable(k);
				//printf("a %.2f\n",(population[i])->subpopulation[j][k]);
			}
		
			//append objective to the individual
			problem->objectiveFunction((population[i])->subpopulation[j], ((population[i])->subpopulation[j] + problem->problem_size));
			population[i]->available_index= (population[i])->subpopulation_size;
		}
	}


//	plotHistogram("fitness", tmp,population_size);
	
//	int best_individual= getBestIndividual();
//	double best_fitness;
//	problem->objectiveFunction(population[best_individual], &best_fitness);

//	printf("INITIAL best fitness found: %f\n",best_fitness);

	///////////////////BEGIN LOOP////////////////////////////////////////

	for(i=0;i<max_generations;i++)
	{
//		for(int j=0;j<population_size;++j)
//		{	
//			problem->objectiveFunction(population[j],&tmp[j]);
//		}

		newGeneration();

		/*
		if(i==5000)
		{
			storeSolutions("5000solutions");
		}
		if(i==10000)
		{
			storeSolutions("10000solutions");
		}
		*/
		
	}

	
	int random_individual= rand()%subpopulation_size;
	memcpy(*solution,population[0]->subpopulation[0],problem->problem_size*sizeof(double));

//	best_individual= getBestIndividual();
//	problem->objectiveFunction(population[best_individual], &best_fitness);

//	printf("best fitness found: %f\n",best_fitness);

	//copy solution to the vector of solution passed
	//*solution=(double*)malloc(sizeof(double)*problem->problem_size);

//	memcpy(*solution,population[best_individual],problem->problem_size*sizeof(double));
//	printArray(population[best_individual], problem->problem_size);
//	printArray(*solution, problem->problem_size);
	
//	return best_fitness;
	return 1;

}

double Subpopulation_Framework::optimizeDebug(Optimization_Problem* optimization_problem, int number_of_problems, double** solution)
{
/*	int i;

	if(number_of_problems!=1)
	{
		printf("ERROR: Differential Evolution can only solve one problem at a time, it is not multi-objective\n");
		exit(1);
	}

	
	/////////////// Allocating memory////////////////////

	problem= optimization_problem;
	
	trial_vector=(double*)malloc(sizeof(double)*problem->problem_size);
	
	
	//allocating 
	allocatePopulations();


	///////////////// initialization generate random population //////////////////////
	

	for(i=0;i<population_size;++i)
	{	
		generateRandomIndividual();
	
		//printf("random %.2f\n",random.uniform(0.0,0.99));
		
		problem->objectiveFunction(population[i], &tmp[i]);
	}

	plotHistogram("fitness", tmp,population_size);
	
	int best_individual= getBestIndividual();
	double best_fitness;
	problem->objectiveFunction(population[best_individual], &best_fitness);

	printf("INITIAL best fitness found: %f\n",best_fitness);
	double discard_result;
	problem->printDetails(population[best_individual], &discard_result);

	///////////////////BEGIN LOOP////////////////////////////////////////

	for(i=0;i<max_generations;i++)
	{
//		char filename[64];

//		for(int j=0;j<population_size;++j)
//		{	
//			problem->objectiveFunction(population[j], &tmp[j]);
//		}

		//sprintf(filename,"fitness_before_gen_%d",i);

		newGeneration();
		
//		sprintf(filename,"fitness_gen_%d",i);
//		plotHistogram(filename, tmp,population_size);
//		best_individual= getBestIndividual();
//		problem->objectiveFunction(population[best_individual], &best_fitness);

//		printf("generation %d best fitness %f\n", i, best_fitness);
	
	}
	
//	for(i=0;i<population_size;++i)
//	{	
//		tmp[i]= problem->objectiveFunction(population[i]);
//	}
//	plotHistogram("fitnessCLuster", tmp,population_size);
	
//	best_individual= getBestIndividual();
//	problem->objectiveFunction(population[best_individual], &best_fitness);

//	printf("best fitness found: %f\n",best_fitness);
//	problem->printDetails(population[best_individual], &discard_result);

	//copy solution to the vector of solution passed
	*solution=(double*)malloc(sizeof(double)*problem->problem_size);

	memcpy(*solution,population[best_individual],problem->problem_size*sizeof(double));
//	printArray(population[best_individual], problem->problem_size);
//	printArray(*solution, problem->problem_size);
	
//	return best_fitness;
*/	return 1;

}

int Subpopulation_Framework::newGeneration()
{
	int i,j;

	//printf("generation %d\n",generation);
			
	Novelty_Subpopulation* novelty_subpop= (Novelty_Subpopulation*) population[number_of_subpopulations-1];
	
	for(i=0;i<number_of_subpopulations;++i)
	{
		(population[i])->preProcess();
	}
	
	//for all common subpopulations (the tables with the single objectives)
	for(i=0;i<number_of_subpopulations;++i)
	{
		for(j=0; j<population[i]->subpopulation_size;++j)
		{

			//OPERATORS
		
			//create the mutant vector
			mutationOperator(i);	

			//create the trial vector, based on the mutant vector and original vector
			crossoverOperator(i,j);
		
			//append objective to the individual
			problem->objectiveFunction(trial_vector, (trial_vector + problem->problem_size));
			

			//SELECTION 

			//Subpopulation executes selection pressure
			population[i]->selectionPressure(trial_vector,j);

			//insert in the novelty population archive
			novelty_subpop->addIndividual(trial_vector);
		}
	}

	generation++;

	return 0;
}

/*
int Subpopulation_Framework::getBestIndividual()
{
	int i;
	int best_index=0;
	double best_fitness;
	problem->objectiveFunction(population[best_index], &best_fitness);

	for(i=1;i<population_size;++i)
	{	
		double individual_fitness;
		problem->objectiveFunction(population[i], &individual_fitness);

		if(individual_fitness > best_fitness)
		{
			best_index= i;
			problem->objectiveFunction(population[best_index], &best_fitness);
		}
	}
	
	return best_index;
}
*/

void Subpopulation_Framework::generateRandomIndividual()
{
	int j;

	for(j=0;j<problem->problem_size;++j)
	{
		trial_vector[j]= generateRandomVariable(j);
	}
}

/*
void Subpopulation_Framework::generateRandomIndividual(int individual)
{
	int j;

	for(j=0;j<problem->problem_size;++j)
	{
		population[individual][j]= generateRandomVariable(j);
	}
}
*/
double Subpopulation_Framework::generateRandomVariable(int variable)
{
	return (random->uniform(0.0,1.0)*(max_limit*(variable+1)*2 - min_limit) + min_limit);	
	//return (random->uniform(0.0,1.0)*(max_limit - min_limit) + min_limit);	
}

void Subpopulation_Framework::allocatePopulations()
{
	int i=0;
	
	//set the number of objectives (number of subpopulations)
	number_of_subpopulations= number_of_problems +1;

	//for each objective, one subpopulation
	population= (Subpopulation**)malloc(sizeof(Subpopulation*)*number_of_subpopulations);

	//all the problems will have one classic single objective subpopulation
	for(i=0;i<number_of_problems;++i)
	{	
		population[i]= (Subpopulation*) new Classic_Subpopulation(i, 1*subpopulation_size, number_of_problems, problem->problem_size);
	}

	//add an average objective subpopulation
	//population[i]= (Subpopulation*) new Average_Subpopulation(subpopulation_size, number_of_problems, problem->problem_size);
	//i++;
	
	//population[i]= (Subpopulation*) new Pareto_Subpopulation(subpopulation_size, number_of_problems, problem->problem_size);
//	population[i]= (Subpopulation*) new GDE3_Subpopulation(subpopulation_size*8, number_of_problems, problem->problem_size);
//	i++;
	population[i]= (Subpopulation*) new Novelty_Subpopulation(subpopulation_size*5, number_of_problems, problem->problem_size);
	i++;
		
}
		
void Subpopulation_Framework::storeSolutions(const char* filename)
{
	int i;

	//all subpopulations store their solutions
	for(i=0;i<number_of_subpopulations;++i)
	{	
		//printf("Storing subpopulation %d\n",i);
		population[i]->storeSubpopulation(filename);
	}
	
	//population[0]->storeSubpopulation(filename);
	
}

// new_fitness > best_fitness ? And treat nans
/*bool Subpopulation_Framework::isGreater(double new_fitness, double best_fitness)
{
	//if best_fitness is nan
	//or if new_fitness is not nan and new_fitness is greater than best_fitness
	if( (isnan(best_fitness)) || (!isnan(new_fitness) && new_fitness > best_fitness) )
	{
		return true;
	}
	else
	{
		return false;
	}
}


// new_fitness < best_fitness ? And treat nans
bool Subpopulation_Framework::isLower(double new_fitness, double best_fitness)
{
	//if best_fitness is nan
	//or if new_fitness is not nan and new_fitness is greater than best_fitness
	if( (isnan(best_fitness)) || (!isnan(new_fitness) && new_fitness < best_fitness) )
	{
		return true;
	}
	else
	{
		return false;
	}
}

*/
