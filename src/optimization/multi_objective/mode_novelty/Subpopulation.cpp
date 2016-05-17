
#include"Subpopulation.h"

void Subpopulation::insert(double* individual)
{
	//if there is space on the subpopulation available yet
	if(available_index < subpopulation_size)
	{
		memcpy(subpopulation[available_index], individual, sizeof(double)*individual_size);

		ascendHeap(available_index);
		available_index++;
	}
	//if there isnt space available, copy to the lowest fit individual (top node)
	else
	{
		memcpy(subpopulation[0], individual, sizeof(double)*individual_size);

		descendHeap(0);
	}

}

void Subpopulation::descendHeap(int index)
{
	int son1= index*2 + 1;
	int son2= index*2 + 2;

	while(true)
	{
		if(son1<subpopulation_size && !weaker(subpopulation[index],subpopulation[son1])) 
		{
			//swap son1 and index
			double* tmp= subpopulation[index];
			subpopulation[index]= subpopulation[son1];
			subpopulation[son1]= tmp;

			index= son1;
			son1= index*2 + 1;
			son2= index*2 + 2;
		}
		else
		{
			if(son2<subpopulation_size && !weaker(subpopulation[index],subpopulation[son2]))
			{
				//swap son2 and index
				double* tmp= subpopulation[index];
				subpopulation[index]= subpopulation[son2];
				subpopulation[son2]= tmp;
			
				index= son2;
				son1= index*2 + 1;
				son2= index*2 + 2;
			}
			else
			{
				break;
			}
		}

	}
}

void Subpopulation::ascendHeap(int index)
{
	int parent= floor( (index-1)/2 );

	while(true)
	{
		if(weaker(subpopulation[index],subpopulation[parent])) 
		{
			//swap son1 and index
			double* tmp= subpopulation[index];
			subpopulation[index]= subpopulation[parent];
			subpopulation[parent]= tmp;

			index= parent;
			parent= floor( (index-1)/2 );
			
		}
		else
		{
			break;
		}

	}
}

//test if the individual is stronger (not weaker) than the weakest individual (top individual in subpopulation)
//if it is stronger, insert it
void Subpopulation::testInsert(double* individual)
{
	//printf("%d %d %p",available_index, subpopulation_size, subpopulation[0]);

	if(available_index<subpopulation_size || !weaker(individual,subpopulation[0])) 
	{
		insert(individual);
	}
}

void Subpopulation::printSubpopulation()
{
	printMatrix(subpopulation,available_index, individual_size);
}

void Subpopulation::storeSubpopulation(const char* filename)
{
	writeCSV(filename, subpopulation,available_index, individual_size,"a");
}
