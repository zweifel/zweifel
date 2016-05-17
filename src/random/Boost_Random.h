/***************************************************
 * Boost Random - Interface
 *
 * Very slow when compared to other libraries, 
 * but still flexible(can change easily the random generator) 
 * and with good randomness.
 *
 * **************************************************/




#ifndef BOOST_RANDOM_H
#define BOOST_RANDOM_H

#include"Random.h"
#include<boost/random/uniform_real.hpp>
#include <boost/random/variate_generator.hpp>
#include<boost/random/linear_congruential.hpp>
#include<boost/random/uniform_int.hpp>
#include<boost/random/mersenne_twister.hpp>



// This is a typedef for a random number generator.
// // Try boost::mt19937 or boost::ecuyer1988 instead of boost::minstd_rand
//typedef boost::minstd_rand base_generator_type;
typedef boost::mt11213b base_generator_type;
//typedef boost::rand48 base_generator_type;

class Boost_Random: public Random
{
	private:
	
		base_generator_type generator;
		boost::variate_generator< base_generator_type&, boost::uniform_real<> >* uni01;


	public:
		
		Boost_Random(unsigned int seed);
		~Boost_Random();

		int uniform(int min, int max);
		double uniform(double min, double max);
		//return random result uniformly distributed between [0,1)
		double uniform();	
	
};

#endif
