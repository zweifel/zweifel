
#include"Problem_Test.h"

Problem_Test::Problem_Test()
{
	printf("Optimization Problem Testing ...\n\n");
	//printf("This is not an Optimization Algorithm\n");
	//printf("Made to test Optimization Problems!\n");
}

Problem_Test::~Problem_Test()
{

}


double Problem_Test::optimize(Optimization_Problem* problem, int number_of_problems, double** solution)
{

}

double Problem_Test::optimizeDebug(Optimization_Problem* optimization_problem, int number_of_problems, double** solution)
{

}


void Problem_Test::testSolution(double* chromosome, Optimization_Problem* problem)
{
	double best_fitness;
	problem->objectiveFunction(chromosome, &best_fitness);

	printf("Best Fitness %f\n",best_fitness);

}

/*void Problem_Test::testSolution(double* chromosome, Optimization_Problem* problem)
{
	double best_fitness;
	problem->objectiveFunction(chromosome, &best_fitness);

}
*/
