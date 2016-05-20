
#include"GDE3.h"
#include"unistd.h"
#include"random/State_of_Art_Random.h"
#include"time.h"
#include"../problems/WFG_Problem.h"

int main()
{
	//comparison NSGA 2
	//generations= 500 
	//population_size= 1300

	double max_limit = 1;
	double min_limit = 0;
	int population_size= 100;
	//int subpopulation_size= 150;
	
	int position_parameter=4;
	int distance_parameter=20;
	//int problem_size= position_parameter + distance_parameter;
	int number_of_problems=2;
	//int generations= 250;
	int generations= 25000;

	double F=0.1;
	double CR=0.1;
	//double mutation_rate=0.0;
	
	printf("number of problems %d\n", number_of_problems);
	printf("population size %d\n",population_size);
	printf("max_limit %f\n",max_limit);
	printf("min_limit %f\n",min_limit);
	printf("F %f\n", F);
	printf("CR %f\n", CR);

	Random* random= new State_of_Art_Random(time(NULL));

	//Optimization_Problem* problem= new Ripple(problem_size);
	Optimization_Problem* problem= new WFG_Problem(WFG8, position_parameter, distance_parameter, number_of_problems);
			
	//Optimization_Method* method2= new Differential_Evolution( 100, population_size, max_limit, min_limit, F, CR, random);
	GDE3* method2= new GDE3( generations, population_size, max_limit, min_limit, F, CR, random);
	
	//Optimization_Method* method;

	double* solution;
/*
	double a[2];
	//double s[]={1,1,1,1,1,1};
	double s[]={1.79478,0.0206342,2.1,2.8,3.5,4.2};
	problem->objectiveFunction(s,a);
	printf("iii  %f %f\n",a[0], a[1]);
*/				
	double result= method2->optimize(problem, number_of_problems ,&solution);
	printf("Result %f\n", result);
	//printf("Result %f\n",method2->optimizeDebug(problem, number_of_problems ,&solution));

	//printf("Solution found:\n");
	//printArray(solution,problem_size);
//   	method2->storeSolutions("solutions");
		
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
