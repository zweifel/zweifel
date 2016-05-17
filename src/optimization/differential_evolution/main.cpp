
#include"Differential_Evolution.h"
#include"Ripple.h"
#include"common.h"
#include"unistd.h"
#include"random/State_of_Art_Random.h"
#include"time.h"
#include"unistd.h"

int main()
{
	double max_limit = sqrt(PI/2);
	double min_limit = -sqrt(PI/2);
	int population_size= 40;
	int problem_size= 10;

	double F=0.5;
	double CR=1.0;
	int max_generations=10;
	//double mutation_rate=0.0;
	
	printf("population size %d\n",population_size);
	printf("max_limit %f\n",max_limit);
	printf("min_limit %f\n",min_limit);
	printf("F %f\n", F);
	printf("CR %f\n", CR);

	Random* random= new State_of_Art_Random(time(NULL));

	Optimization_Problem* problem= new Ripple(problem_size);
			
	Optimization_Method* method2= new Differential_Evolution( max_generations, population_size, max_limit, min_limit, F, CR, random);
	
	Optimization_Method* method;

	double* solution= (double*)malloc(sizeof(double)*problem_size+2);
				
	printf("Result %f\n",method2->optimizeDebug(problem, 1,&solution));
	

	//testing the use of previous individuals
	
	sleep(3);

	Differential_Evolution* de= (Differential_Evolution*) method2;

	de->keepPreviousIndividuals();
	
	problem= new Ripple(problem_size+3);
	
	printf("Result %f\n",method2->optimizeDebug(problem, 1,&solution));

	printf("Solution found:\n");
	printArray(solution,problem_size+2);
		
/*

	double result;
	float i,j;
	float step=0.1;
	int k;

	FILE* fp=fopen("data","w");
				
	fprintf(fp,"crossover\tselection_pressure\n");	

	for(i=0.0f ; i<=1.0 ;i+=step)
	{
		crossing_over_probability= i;

		for(j=0.0f ; j<=1.0 ;j+=step)
		{
			selection_pressure= j;
			bool achieved_optimum=true;
			bool already_mistaken=false;

			for(k=0;k<100;k++)
			{
				//sleep(1);

				Optimization_Method* method= new Goldberg_GA( population_size, max_limit, min_limit, selection_pressure, crossing_over_probability, mutation_rate);

				result= method->optimize(problem);

				printf("result %f\n",result);

				delete method;
			
				if(already_mistaken && result > 0.001)
				///if(already_mistaken && result < 0.999)
				{
					achieved_optimum=false;
					break;
				}
				else
				{
					if(result > 0.001)
					//if(result < 0.999)
					{
						already_mistaken=true;
					}
				}
			}
					
			if(achieved_optimum)
				fprintf(fp,"%.2f\t%.2f\t\n",i,j);	

		}
			
		//fprintf(fp,"\n");	

	}
	
	fclose(fp);

*/	
	return 0;
}
