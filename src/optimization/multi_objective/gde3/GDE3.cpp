
#include"GDE3.h"

// random 	The random variable should be initialized before
// F		Should be between [0,2]	
// CR		Should be between [0,1]	
GDE3::GDE3(int max_generations, int population_size, double max_limit, double min_limit, float F, float CR, Random* random)
{
	generation=1;
	this->max_generations= max_generations;
	
	this->population_size= population_size;

	//the maximum population that can be stored 
	//(sometimes the GDE3 increases a bit the size of the population from between generatinons)
	max_population_size= 2*population_size; 

	this->max_limit= max_limit;
	this->min_limit= min_limit;

	this->random=random;

	tmp=(double*)malloc(sizeof(double)*max_population_size);
	population= (double**)malloc(sizeof(double*)*max_population_size);
	tmp_population= (double**)malloc(sizeof(double*)*max_population_size);
	index_array= (int*)malloc(sizeof(int)*max_population_size);
	diversity_dist= (double*)malloc(sizeof(double)*max_population_size);

	this->F= F;
	this->CR= CR;
	
	printParameters();	

	//if the problem size was already determined 
	//(this is usually defined when the problem is defined)
	problem_previously_defined=false;

	//variables for continuying evolution later on
	keep_previous_individuals=false;
	
}

GDE3::~GDE3()
{
	int i;

	if(problem_previously_defined==true)
	{
		freeProblemMemory();
	}

	free(population);
	free(tmp);
	free(tmp_population);
	free(index_array);
	free(diversity_dist);
		
}

void GDE3::keepPreviousIndividuals()
{
	keep_previous_individuals=true;
}

void GDE3::mutationOperator(int individual)
{
	int i;

	double* r1;
	double* r2;
	double* r3;
	
	//choosing 3 individuals from any subpopulations randomly
	
	int random_subpop;
	int random_ind;
/*	
	if(random->uniform(0.0,1.0)>0.5)
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
		F=random->uniform(0.0,2.0);
		trial_vector[i]= r1[i] + F*(r2[i] - r3[i]);
	
	}
*/
		
	//F=random->uniform(0.0,2.0);

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
			//F=random->uniform(0.0,1.0);
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

	
}

void GDE3::crossoverOperator(int subpop, int individual)
{
	int i;
	
	//choose a random index, to ensure that at least this will be inserted in the trial_vector
	int random_index= random->uniform(0,problem->problem_size-1);
	
	//choose a random individual
	//int random_subpop= random->uniform(0,number_of_subpopulations-1);
	//int random_ind= random->uniform(0,population[random_subpop]->available_index-1);
        
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

	for(i=0;i<problem->problem_size;++i)
	{

		if(random_index != i && random->uniform() > CR)
		{
			trial_vector[i]= population[individual][i];
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

void GDE3::printParameters()
{
	printf("population size %d\n",population_size);
	printf("max_limit %f\n",max_limit);
	printf("min_limit %f\n",min_limit);
	printf("F %f\n", F);
	printf("CR %f\n", CR);
	printf("max population size %d\n",max_population_size);
	printf("number of problems %d\n",number_of_problems);
}

double GDE3::optimize(Optimization_Problem* optimization_problem, int number_of_problems, double** solution)
{
	int i,k;

	if(number_of_problems==1)
	{
		printf("ERROR: MODE can only solve multiple problems at a time, it is not single-objective\n");
		exit(1);
	}
	
	/////////////// Allocating memory////////////////////

	problem= optimization_problem;
	this->number_of_problems= number_of_problems;

	//if no problem was defined before, just allocate the memory
	//otherwise, check if there is already available from last problem and manage memory accordingly
	if(problem_previously_defined==false)
	{
		allocateProblemMemory();
	}
	else
	{
		//if the allocated memory is not enough
		if(allocated_problem_size < problem->problem_size)
		{
			if(keep_previous_individuals == false)
			{
				freeProblemMemory();

				allocateProblemMemory();
			}
			else
			{
				printf("reallocating\n");

				reallocateProblemMemory();
			}
		}
	}

	


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

	for(i=0;i<population_size;++i)
	{
		//if it is the first time it is evolving or any occurence that does not defined the problem before 
		//or if it was not set to keep previous individuals
		//then generate full random individuals
		if(problem_previously_defined==false || keep_previous_individuals == false)
		{
			for(k=0; k<problem->problem_size; ++k)
			{
				population[i][k]= generateRandomVariable(k);
				//printf("a %.2f\n",(population[i])->subpopulation[j][k]);
			}
		}
		//partially generate individuals
		else
		{
			for(k=last_problem_size; k<problem->problem_size; ++k)
			{
				population[i][k]= generateRandomVariable(k);
				//printf("a %.2f\n",(population[i])->subpopulation[j][k]);
			}
		}
	
		//append objective to the individual
		problem->objectiveFunction(population[i], population[i] + problem->problem_size);
	}
	current_pop_size=population_size;

	problem_previously_defined=true;

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
		if(i==500)
		{
			storeSolutions("500_solutions");
		}
		if(i==2000)
		{
			storeSolutions("2000_solutions");
		}
		if(i==10000)
		{
			storeSolutions("10000_solutions");
		}*/
	}
	
	int best_individual= getBestIndividual();
//	problem->objectiveFunction(population[best_individual], &best_fitness);

//	printf("best fitness found: %f\n",best_fitness);

	//copy solution to the vector of solution passed
	//*solution=(double*)malloc(sizeof(double)*problem->problem_size);

	memcpy(*solution,population[best_individual],problem->problem_size*sizeof(double));
//	printArray(population[best_individual], problem->problem_size);
//	printArray(*solution, problem->problem_size);
	
//	return best_fitness;

	//update the size of the problem size
	last_problem_size= problem->problem_size;

	return 1;

}

double GDE3::optimizeDebug(Optimization_Problem* optimization_problem, int number_of_problems, double** solution)
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

int GDE3::newGeneration()
{
//	printf("generation %d ",generation);

	int i;
			
	//for all common subpopulations (the tables with the single objectives)
	for(i=0;i<population_size;++i)
	{
		//create the mutant vector
		mutationOperator(i);	

		//create the trial vector, based on the mutant vector and original vector
		crossoverOperator(0,i);
	
		//append objective to the individual
		problem->objectiveFunction(trial_vector, (trial_vector + problem->problem_size));
			
		double* parent= population[i];

		//SELECTION

		int result= isWeakConstraintDominated(trial_vector,parent);

		//if the new individual (trial vector) dominates the parent
		if(result==1)
		{
			memcpy(population[i], trial_vector, individual_size*sizeof(double));
		}
		else
		{
			//if neither one dominates, add one more individual to the population
			if(result==0)
			{
				//copy the trial to a new individual slot (previously allocated)
				memcpy(population[current_pop_size], trial_vector, individual_size*sizeof(double));
				
				//increase the size of the population
				current_pop_size++;		
			}
		}

	//	printf("individual\n");
	//	printArray(trial_vector, population[i]->individual_size);
		//insert in the novelty population archive
	}

	

	//REDUCING THE SIZE OF THE POPULATION TO ITS ORIGINAL VALUE

//	printf("        curr %d pop %d\n",current_pop_size, population_size);

	if(current_pop_size > population_size)
	{
		useCrowdingdistance();		
	}

/*
	for(i=0;i<population_size;++i)
	{
		
		
		double fitness_trial, fitness_father;
		problem->objectiveFunction(trial_vector, &fitness_trial);
		problem->objectiveFunction(population[i], &fitness_father);

		//selection, test if the trial vector is better than the original vector
		if(fitness_trial > fitness_father)
		{
			//copy the trial to the original vector
			memcpy(population[i], trial_vector, problem->problem_size*sizeof(double));
		}
		
		

		//problem->objectiveFunction(population[i], &tmp[i]);
		for(j=0;j<number_of_subpopulations;++j)
		{
			population[j]->testInsert(trial_vector);
		}
	}*/

	generation++;

	return 0;
}

void GDE3::allocateProblemMemory()
{
	allocated_problem_size= problem->problem_size*2;

	individual_size= allocated_problem_size + number_of_problems;
	
	//trial_vector=(double*)malloc(sizeof(double)*problem->problem_size);
	trial_vector = (double*)malloc(sizeof(double)*(allocated_problem_size + number_of_problems));
	
	//allocating 
	allocatePopulations();
}

void GDE3::freeProblemMemory()
{
	int i;

	free(trial_vector);

	//for each objective, one subpopulation
	for(i=0;i<max_population_size;++i)
	{	
		free(population[i]);
	}
	
	//tmp population
	for(i=0;i<max_population_size;++i)
	{	
		free(tmp_population[i]);
	}
}

void GDE3::reallocateProblemMemory()
{
	int i;

	allocated_problem_size= problem->problem_size*2;

	individual_size= allocated_problem_size + number_of_problems;
	
	//trial_vector=(double*)malloc(sizeof(double)*problem->problem_size);
	trial_vector = (double*)realloc(trial_vector, sizeof(double)*(allocated_problem_size + number_of_problems));
	
	//for each objective, one subpopulation
	for(i=0;i<max_population_size;++i)
	{	
		population[i]= (double*)realloc(population[i],sizeof(double)*(allocated_problem_size + number_of_problems));
	}
	
	//tmp population
	for(i=0;i<max_population_size;++i)
	{	
		tmp_population[i]= (double*)realloc(tmp_population[i],sizeof(double)*(allocated_problem_size + number_of_problems));
	}
}


int GDE3::getBestIndividual()
{
	int i;
	int best_index=0;
	double best_fitness;
	//problem->objectiveFunction(population[best_index], &best_fitness);
	best_fitness= population[best_index][problem->problem_size];

	for(i=1;i<population_size;++i)
	{	
		double individual_fitness;
		individual_fitness= population[i][problem->problem_size];

		if(individual_fitness > best_fitness)
		{
			best_index= i;
			best_fitness= individual_fitness;
		}
	}
	
	return best_index;
}


void GDE3::generateRandomIndividual()
{
	int j;

	for(j=0;j<problem->problem_size;++j)
	{
		trial_vector[j]= generateRandomVariable(j);
	}
}

/*
void GDE3::generateRandomIndividual(int individual)
{
	int j;

	for(j=0;j<problem->problem_size;++j)
	{
		population[individual][j]= generateRandomVariable(j);
	}
}
*/
double GDE3::generateRandomVariable(int variable)
{
	double a= (random->uniform(0.0,1.0)*(max_limit - min_limit) + min_limit);	
	//printf("%.2f\n",a);
	return a; 
	//return (random->uniform(0.0,1.0)*(max_limit - min_limit) + min_limit);	
}

void GDE3::allocatePopulations()
{
	int i;
	
	//set the number of objectives (number of subpopulations)
	//number_of_subpopulations= number_of_problems +1;

	//for each objective, one subpopulation
	for(i=0;i<max_population_size;++i)
	{	
		population[i]= (double*)malloc(sizeof(double)*(allocated_problem_size + number_of_problems));
	}
	
	//tmp population
	for(i=0;i<max_population_size;++i)
	{	
		tmp_population[i]= (double*)malloc(sizeof(double)*(allocated_problem_size + number_of_problems));
	}
		
}
		
void GDE3::storeSolutions(const char* filename)
{

//	printf("Storing subpopulation \n");
	writeCSV(filename, population, current_pop_size, problem->problem_size + number_of_problems,"a");
	
}

// new_fitness > best_fitness ? And treat nans
/*bool GDE3::isGreater(double new_fitness, double best_fitness)
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
bool GDE3::isLower(double new_fitness, double best_fitness)
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

//return 1 if trial dominates parent
//return -1 if parent dominates trial
//return 0 if neither vectors dominate each other
int GDE3::isWeakConstraintDominated(double* trial, double* parent)
{
	isNondominated(trial,parent);
	//test if the trial is completely dominated by the parent
	if(!isNondominated(trial,parent))
	{
		return -1;
	}
	else
	{
		//test if the parent is completely dominated by the trial
		if(!isNondominated(parent,trial))
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}

}

//Is individual a non dominated by individual b?
bool GDE3::isNondominated(double* a, double* b)
{
	int i;

	bool not_equal=false;

	for(i=0; i<number_of_problems; ++i)
	{
		//if some a's solution is greater than b's, it is non dominated
		if(a[problem->problem_size + i] >  b[problem->problem_size + i])
		{
			return true;
		}
		else
		{
			if(a[problem->problem_size + i] <  b[problem->problem_size + i])
			{
				not_equal=true;
			}

		}
	}

	if(not_equal)
	{
		return false;
	}
	else
	{
		return true;
	}
}

void GDE3::useCrowdingdistance()
{
	list<double*> all_fronts;

	//create a List with all fronts together
	for(int i=0; i<current_pop_size; ++i)
	{
		//NOTE: it is important to create a copy, because when passing the fronts back to the population 
		//if the memory is not a copy it will start messing up with the logic 
		//in other words, the Address of the new population and the fronts will be the same!!!

		//Storing a copy of the population
		memcpy(tmp_population[i], population[i], sizeof(double)*individual_size);

		//inserting the population copy
		all_fronts.push_back(tmp_population[i]);
	}
	
	int new_pop_size=0;
	//	printf("all fronts %d new pop %d\n",all_fronts.size(), new_pop_size);

	//processing all fronts
	//copying all fronts to the population, 
	//until the population size constraint is violated (or exactly fulfilled)
	while(new_pop_size < population_size)
	{
		vector<double*> front;
		
	//	printf("curr %d all fronts %d new pop %d front %d\n",current_pop_size, all_fronts.size(), new_pop_size, front.size());

		//create next front and remove elements from all_fronts
		createFront(all_fronts, front, problem->problem_size, number_of_problems);
	
		new_pop_size+= front.size();

	//	printf("curr %d all fronts %d new pop %d front %d\n",current_pop_size, all_fronts.size(), new_pop_size, front.size());

		//if the resulting population size is not more than the default, copy it.
		if(new_pop_size <= population_size)
		{
			for(uint i = 0; i < front.size(); ++i)
			{
				memcpy(population[i],front[i],sizeof(double)*individual_size);
			}
		}
		else
		{
			int k=10;

			//crowdingdistance(front.data(), front.size(), problem->problem_size, number_of_problems, index_array, diversity_dist);
			kNearestNeighbors(front.data(), front.size(), problem->problem_size, number_of_problems, index_array, diversity_dist, k);
			
			//will be a negative difference
			int diff= population_size - new_pop_size;

			for(uint i = 0; i < front.size() + diff; ++i)
			{
				memcpy(population[i],front[index_array[i]],sizeof(double)*individual_size);
			}

		}
		
	}

	current_pop_size= population_size;

//	crowdingdistance(population, current_pop_size, problem->problem_size, number_of_problems, index_array, crowd_dist);

	
//	for(int i=0; i<current_pop_size; ++i)
//	{
//		memcpy(population[i], tmp_population[index_array[i]], sizeof(double)*individual_size);
//	}

	/*printArray(index_array,current_pop_size);
	printArray(crowd_dist, current_pop_size);

	for(int i=0; i<current_pop_size; ++i)
	{
		printf("%.2f ",crowd_dist[index_array[i]]);
	}
	*/

	

	//exit(1);
}
