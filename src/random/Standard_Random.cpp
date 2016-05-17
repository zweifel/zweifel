
#include"Standard_Random.h"


Standard_Random::Standard_Random(unsigned int seed)
{
	srandom(seed);
}

Standard_Random::~Standard_Random()
{

}

int Standard_Random::uniform(int min, int max)
{
	int range= max - min + 1;

	return (int)range*(random()/(RAND_MAX +1.0)) + min;
}

double Standard_Random::uniform(double min, double max)
{
	return ((double)random()/(RAND_MAX + 1.0))*(max - min) +  min;

}

double Standard_Random::uniform()
{
	return (double)random()/(RAND_MAX + 1.0);

	//return (double)rand()/(double)RAND_MAX;
}
