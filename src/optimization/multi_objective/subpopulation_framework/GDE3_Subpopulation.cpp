

#include"GDE3_Subpopulation.h"


GDE3_Subpopulation::GDE3_Subpopulation(int subpopulation_size, int number_of_problems, int problem_size)
{
	this->problem_size= problem_size;
	this->subpopulation_size= subpopulation_size;
	this->max_subpopulation_size= 2*subpopulation_size;

	available_index=0;
	individual_size=number_of_problems + problem_size;
	this->number_of_problems= number_of_problems;

	subpopulation= (double**)malloc(sizeof(double*)*max_subpopulation_size);
	for(int i=0;i<max_subpopulation_size; ++i)
	{	
		subpopulation[i]= (double*)malloc(sizeof(double)*(individual_size));		
	}
	
	tmp_subpopulation= (double**)malloc(sizeof(double*)*max_subpopulation_size);
	for(int i=0;i<max_subpopulation_size; ++i)
	{	
		tmp_subpopulation[i]= (double*)malloc(sizeof(double)*(individual_size));		
	}

	index_array= (int*)malloc(sizeof(int)*max_subpopulation_size);
	diversity_dist= (double*)malloc(sizeof(double)*max_subpopulation_size);

	k=10;

	current_pop_size=subpopulation_size;

	printf("GDE3 subpopulation\n");
}
	
//Is individual a weaker than individual b?
bool GDE3_Subpopulation::weaker(double* a, double* b)
{
/*	int i;

	for(i=0; i<number_of_problems; ++i)
	{
		if(a[problem_size + i] <  b[problem_size + i])
		{
			return true;
		}
	}
*/
	return false;
}
	
void GDE3_Subpopulation::selectionPressure(double* new_individual, int parent_index)
{

	double* parent= subpopulation[parent_index];

	int result= isWeakConstraintDominated(new_individual,parent);
	

	//if the new individual (trial vector) dominates the parent
	if(result==1)
	{
		memcpy(subpopulation[parent_index], new_individual, individual_size*sizeof(double));
	}
	else
	{
		//if neither one dominates, add one more individual to the population
		if(result==0)
		{
//	printf("3 curr %d sub %d max %d\n",current_pop_size, subpopulation_size, max_subpopulation_size);
			//copy the trial to a new individual slot (previously allocated)
			memcpy(subpopulation[current_pop_size], new_individual, individual_size*sizeof(double));

			//increase the size of the population
			current_pop_size++;
		}
	}
	
}

//Is individual a non dominated by individual b?
bool GDE3_Subpopulation::isNondominated(double* a, double* b)
{
        int i;

        bool not_equal=false;

        for(i=0; i<number_of_problems; ++i)
        {
                //if some a's solution is greater than b's, it is non dominated
                if(a[problem_size + i] >  b[problem_size + i])
                {
                        return true;
                }
                else
                {
                        if(a[problem_size + i] <  b[problem_size + i])
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

void GDE3_Subpopulation::preProcess()
{

	//If pop if bigger, reduce it keeping diversity (non dominated sorting + diversity measure)
	if(current_pop_size > subpopulation_size)
	{
		printf("reduce pop\n");
		reduceSubpopulation();
	}

}

void GDE3_Subpopulation::reduceSubpopulation()
{
        list<double*> all_fronts;

        //create a List with all fronts together
        for(int i=0; i<current_pop_size; ++i)
        {
                //NOTE: it is important to create a copy, because when passing the fronts back to the population 
                //if the memory is not a copy it will start messing up with the logic 
                //in other words, the Address of the new population and the fronts will be the same!!!

                //Storing a copy of the population
                memcpy(tmp_subpopulation[i], subpopulation[i], sizeof(double)*individual_size);

                //inserting the population copy
                all_fronts.push_back(tmp_subpopulation[i]);
        }

        int new_pop_size=0;

        //processing all fronts
        //copying all fronts to the population, 
        //until the population size constraint is violated (or exactly fulfilled)
        while(new_pop_size < subpopulation_size)
        {
                vector<double*> front;

                //create next front and remove elements from all_fronts
                createFront(all_fronts, front, problem_size, number_of_problems);

                new_pop_size+= front.size();

                //if the resulting population size is not more than the default, copy it.
                if(new_pop_size <= subpopulation_size)
                {
                        for(uint i = 0; i < front.size(); ++i)
                        {
                                memcpy(subpopulation[i],front[i],sizeof(double)*individual_size);
                        }
                }
                else
                {
                        int k=10;

                        //crowdingdistance(front.data(), front.size(), problem->problem_size, number_of_problems, index_array, diversity_dist);
                        kNearestNeighbors(front.data(), front.size(), problem_size, number_of_problems, index_array, diversity_dist, k);

                        //will be a negative difference
                        int diff= subpopulation_size - new_pop_size;

                        for(uint i = 0; i < front.size() + diff; ++i)
                        {
                                memcpy(subpopulation[i],front[index_array[i]],sizeof(double)*individual_size);
                        }

                }

        }

        current_pop_size= subpopulation_size;

	
}

//return 1 if trial dominates parent
//return -1 if parent dominates trial
//return 0 if neither vectors dominate each other
int GDE3_Subpopulation::isWeakConstraintDominated(double* trial, double* parent)
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

void GDE3_Subpopulation::storeSubpopulation(const char* filename)
{
	//If pop if bigger, reduce it keeping diversity (non dominated sorting + diversity measure)
	if(current_pop_size > subpopulation_size)
	{
		printf("reduce pop\n");
		reduceSubpopulation();
	}

	printf("Storing GDE3 Subpopulation\n");
	writeCSV(filename, subpopulation, subpopulation_size, individual_size,"a");
}
