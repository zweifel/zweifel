
#include"Boost_Random.h"


Boost_Random::Boost_Random(unsigned int seed)
{
	// Define a random number generator and initialize it with a reproducible
	// seed.  (The seed must be an unsigned int)
	//base_generator_type* generator= new base_generator_type(seed);
	
	generator.seed(seed);
	
	//the crazyness of C++ and that the Boost library follows :/
	boost::uniform_real<>uni_dist(0,1);
	uni01 = new boost::variate_generator< base_generator_type&, boost::uniform_real<> >(generator, uni_dist);

}

Boost_Random::~Boost_Random()
{
}

int Boost_Random::uniform(int min, int max)
{
	boost::uniform_int<> int_uni_dist(min,max);
	boost::variate_generator< base_generator_type&, boost::uniform_int<> > uni(generator, int_uni_dist);
	
	return uni();

}

double Boost_Random::uniform(double min, double max)
{
	boost::uniform_real<> real_uni_dist(min,max);
	boost::variate_generator< base_generator_type&, boost::uniform_real<> > uni(generator, real_uni_dist);
	
	return uni();
}

double Boost_Random::uniform()
{
	return (*uni01)();
}
