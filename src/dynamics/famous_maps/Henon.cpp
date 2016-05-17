
#include"Henon.h"

Henon::Henon(double a, double b, double x_init, double y_init)
{
	this->a=a;
	this->b=b;
	this->x=x_init;
	this->y=y_init;

}

Henon::~Henon()
{

}

//set the neuron to resting state
void Henon::restingState()
{
	int i=0;
	for(i=0;i<1000;++i)
	{
		this->iterate(0.0);
	}
}

//ignore input
double Henon::iterate(double input)
{
	double x2,y2;
	
	x2= a -x*x + b*y;
	y2= x;
	
	x= x2;
	y= y2;

	return 0.0;
}
