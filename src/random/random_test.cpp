
#include"random.hpp"
#include"stdio.h"
#include"stdlib.h"
#include"useful/useful_plots.h"
#include"time.h"
#include<boost/random/uniform_real.hpp>
#include <boost/random/variate_generator.hpp>
#include<boost/random/linear_congruential.hpp>
#include"Random.h"
#include"Boost_Random.h"
#include"Standard_Random.h"
#include"State_of_Art_Random.h"

int main()
{
	int i;
	srand(time(NULL));

	double results[1000000];
/*	
	for(i=0;i<1000000;++i)
	{
		//results[i]= rand()%101;
		results[i]= (rand()/(float)RAND_MAX); //(0,1)
	}

	//printf("%d\n",RAND_MAX);

	plotHistogram("rand_results",results,1000000);
*/	

	/*
	randomG* random= new randomG();

	random->randomize(0.345356);

	for(i=0;i<1000000;++i)
	{
		//results[i]= (int)random->uniform(0,100);
		results[i]= random->uniform((double)0.00,(double)1.00);
	}

	plotHistogram("goldberg_random_results",results,1000000);
*/



	Random* r= new State_of_Art_Random(42u);
	//Random* r= new Boost_Random(42u);
	//Random* r= new Standard_Random(42u);
	

//	boost::minstd_rand generator(42u);
//	boost::uniform_real<>uni_dist(0,1);
//	boost::variate_generator< boost::minstd_rand&, boost::uniform_real<> > uni(generator, uni_dist);

	for(i=0;i<1000000;++i)
	{
//		results[i]= uni();
		//results[i]= r->uniform(1,100);
		//results[i]= r->gaussian(0.0,0.125);
		results[i]= r->gaussian(0.0,0.06);
	}

	plotHistogram("boost_random_results",results,1000000);
	


	return 0;
}
