
#include"WFG_Problem.h"

WFG_Problem::WFG_Problem(int problem_type, int position_parameters, int distance_parameters, int number_of_problems)
{
	this->problem_type= problem_type;

	this->k=position_parameters;
	this->l=distance_parameters;
	
	this->problem_size= k + l;

	this->number_of_problems= number_of_problems;
}

WFG_Problem::~WFG_Problem()
{

}

void WFG_Problem::objectiveFunction(double* chromosome, double* result)
{
//	const int k_factor = 2;   // k (# position parameters) = k_factor*( M-1 ) 
//	const int l_factor = 2;   // l (# distance parameters) = l_factor*2

//	const int k = k_factor*( number_of_problems -1 );
//	const int l = l_factor*2;

	vector<double> z(&chromosome[0], &chromosome[problem_size]);
	vector<double> return_vector;

	//test the range of variables
	for(int i=0;i<problem_size;++i)
	{
    		const double bound = 2.0*( i+1 );

		if(chromosome[i] < 0.0 || chromosome[i] > bound)
		{
			for(int j=0;j<number_of_problems;++j)
			{
				result[j]=-999.0;
			}
			return;
		}
	}


	switch(problem_type)
	{
		case WFG1:
			//minimize function (negative)

			//printf("k %d\n",k);
			//printf("number_of_problems %d\n",number_of_problems);
			//printf("z %d\n",z.size());
			return_vector = Problems::WFG1(z, k, number_of_problems);
			memcpy(result, return_vector.data(), number_of_problems*sizeof(double));
			for(int j=0;j<number_of_problems;++j)
			{
				result[j]= -result[j];
			}
			return;
			break;
		case WFG2:
			return_vector = Problems::WFG2(z, k, number_of_problems);
			memcpy(result, return_vector.data(), number_of_problems*sizeof(double));
			for(int j=0;j<number_of_problems;++j)
			{
				result[j]= -result[j];
			}
			return;
			break;
		case WFG3:
			return_vector = Problems::WFG3(z, k, number_of_problems);
			memcpy(result, return_vector.data(), number_of_problems*sizeof(double));
			for(int j=0;j<number_of_problems;++j)
			{
				result[j]= -result[j];
			}
			return;
			break;
		case WFG4:
			return_vector = Problems::WFG4(z, k, number_of_problems);
			memcpy(result, return_vector.data(), number_of_problems*sizeof(double));
			for(int j=0;j<number_of_problems;++j)
			{
				result[j]= -result[j];
			}
			return;
			break;
		case WFG5:
			return_vector = Problems::WFG5(z, k, number_of_problems);
			memcpy(result, return_vector.data(), number_of_problems*sizeof(double));
			for(int j=0;j<number_of_problems;++j)
			{
				result[j]= -result[j];
			}
			return;
			break;
		case WFG6:
			return_vector = Problems::WFG6(z, k, number_of_problems);
			memcpy(result, return_vector.data(), number_of_problems*sizeof(double));
			for(int j=0;j<number_of_problems;++j)
			{
				result[j]= -result[j];
			}
			return;
			break;
		case WFG7:
			return_vector = Problems::WFG7(z, k, number_of_problems);
			memcpy(result, return_vector.data(), number_of_problems*sizeof(double));
			for(int j=0;j<number_of_problems;++j)
			{
				result[j]= -result[j];
			}
			return;
			break;
		case WFG8:
			return_vector = Problems::WFG8(z, k, number_of_problems);
			memcpy(result, return_vector.data(), number_of_problems*sizeof(double));
			for(int j=0;j<number_of_problems;++j)
			{
				result[j]= -result[j];
			}
			return;
			break;
		case WFG9:
			return_vector = Problems::WFG9(z, k, number_of_problems);
			memcpy(result, return_vector.data(), number_of_problems*sizeof(double));
			for(int j=0;j<number_of_problems;++j)
			{
				result[j]= -result[j];
			}
			return;
			break;
	}

	printf("ERROR: No problem_type defined in WFG_Problem class\n");
	exit(1);
	return;
}
		
void WFG_Problem::printDetails(double* variables, double* result)
{
}
