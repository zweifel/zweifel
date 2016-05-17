

#include"Novelty_Subpopulation.h"


Novelty_Subpopulation::Novelty_Subpopulation(int subpopulation_size, int number_of_problems, int problem_size)
{
	this->problem_size= problem_size;
	this->subpopulation_size= subpopulation_size;

	archive_size=0;
	max_archive_size=600;
	available_index=0;
	individual_size=number_of_problems + problem_size;
	this->number_of_problems= number_of_problems;
	generation=0;
	generation_counter=0;
	last_individual_generation=0;

	novelty_threshold=0.0;
	novelty_rejected_counter=0;
	k=10;
//	average_novelty=0.0;

	//allocate subpop
	subpopulation= (double**)malloc(sizeof(double*)*subpopulation_size);
	for(int i=0;i<subpopulation_size; ++i)
	{	
		subpopulation[i]= (double*)malloc(sizeof(double)*(individual_size));		
	}
	
	//allocate archive
	archive= (double**)malloc(sizeof(double*)*max_archive_size);
	for(int i=0;i<max_archive_size; ++i)
	{	
		archive[i]= (double*)malloc(sizeof(double)*(individual_size));		
	}
	nearest_neighbors_distance= (double*)malloc(sizeof(double)*max_archive_size);
	index_array= (int*)malloc(sizeof(int)*max_archive_size);

	//printf("Novelty Search subpop initialized\n");

}
	
//Is individual a weaker than individual b?
bool Novelty_Subpopulation::weaker(double* a, double* b)
{
	int i;

	for(i=0; i<number_of_problems; ++i)
	{
		if(a[problem_size + i] <  b[problem_size + i])
		{
			return true;
		}
	}

	return false;
}
	
void Novelty_Subpopulation::selectionPressure(double* new_individual, int parent_index)
{
	//no selection pressure used 
}

void Novelty_Subpopulation::preProcess()
{
	generation++;
	//printf("generationnn %d\n",generation);
	//printf("%s:%u\n",__FILE__,__LINE__);
	
	//kNearestNeighbors(archive, archive_size, problem_size, number_of_problems, index_array, nearest_neighbors_distance, k);

	for(int i=0;i<subpopulation_size&&i<archive_size; ++i)
	{	
		memcpy(subpopulation[i],archive[rand()%archive_size],individual_size*sizeof(double));
	}
	
	
	//printf("%s:%u\n",__FILE__,__LINE__);
}

void Novelty_Subpopulation::addIndividual(double* individual)
{
	//printf("%d max %d %s:%u\n",archive_size,max_archive_size, __FILE__,__LINE__);
	//printf("%d max %d: %f\n",archive_size,max_archive_size,novelty_threshold);


	//if it is the first or second individual
	//to be added to the archive
	if(novelty_threshold < 0.0001)
	{
		if(archive_size!=0)
		{
			novelty_threshold= individualKNN(individual, archive, archive_size, problem_size, number_of_problems, k, nearest_neighbors_distance);
		}
		else
		{
			novelty_threshold= 0.000;
		}

		//add individual
		memcpy(archive[archive_size],individual,individual_size*sizeof(double));
		
		archive_size++;

	}
	else
	{
		double individual_novelty= individualKNN(individual, archive, archive_size, problem_size, number_of_problems, k, nearest_neighbors_distance);
		//if the individual is greater than the novelty threshold
		//add it to the archive
		if(novelty_threshold < individual_novelty)
		{
			//add individual
			memcpy(archive[archive_size],individual,individual_size*sizeof(double));
			
			archive_size++;

			novelty_rejected_counter=0;
	
			if(generation_counter>1&&last_individual_generation==generation)
			{
				//update novelty threshold
				//with a 5% increase requirement
				novelty_threshold= 1.1*novelty_threshold;
			}
			else
			{
				if(last_individual_generation!=generation)
				{
					generation_counter=0;
				}
				else
				{
					generation_counter++;
				}
				
			}

			last_individual_generation=generation;

		}
		else
		{
			novelty_rejected_counter++;

			if(novelty_rejected_counter>50000)
			{
				novelty_threshold= 0.999*novelty_threshold;
			}
		}
	}
		
	//check if the archive has reached its limit
	if(archive_size == max_archive_size)
	{
		int old_max_archive_size=max_archive_size;
		max_archive_size= 2*max_archive_size;
		archive= (double**)realloc(archive, sizeof(double*)*max_archive_size);
		for(int i=old_max_archive_size;i<max_archive_size; ++i)
		{	
			archive[i]= (double*)malloc(sizeof(double)*(individual_size));		
		}
		nearest_neighbors_distance= (double*)realloc(nearest_neighbors_distance,sizeof(double)*max_archive_size);
		index_array= (int *)realloc(index_array,sizeof(int)*max_archive_size);
	}

	//printf("%s:%u\n",__FILE__,__LINE__);
}

void Novelty_Subpopulation::storeSubpopulation(const char* filename)
{
	//writeCSV(filename, subpopulation,available_index, individual_size,"a");
	writeCSV(filename, archive,archive_size, individual_size,"a");
}
