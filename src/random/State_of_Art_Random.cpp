
#include"State_of_Art_Random.h"


State_of_Art_Random::State_of_Art_Random(unsigned int seed)
{
	init_gen_rand(seed);
}

State_of_Art_Random::~State_of_Art_Random()
{

}

int State_of_Art_Random::uniform(int min, int max)
{
	int range= max - min + 1;

	return (int)range*(genrand_close_open()) + min;
}

double State_of_Art_Random::uniform(double min, double max)
{
	return ((double)genrand_close_open())*(max - min) +  min;

}

double State_of_Art_Random::uniform()
{
	return genrand_close_open(); // [0,1)
}
