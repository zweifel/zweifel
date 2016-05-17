
#include"FitzHugh_Nagumo.h"

FitzHugh_Nagumo::FitzHugh_Nagumo(double a, double b, double tal, double discretization_time)
{
	this->a=a;
	this->b=b;
	this->tal=tal;
	this->discretization_time= discretization_time;

	restingState();
}

FitzHugh_Nagumo::~FitzHugh_Nagumo()
{

}

//set the neuron to resting state
void FitzHugh_Nagumo::restingState()
{
	v=0;
	w=0;


	int i=0;
	for(i=0;i<1000;++i)
	{
		this->iterate(0.0);
	}
}

double FitzHugh_Nagumo::iterate(double input)
{
	I= input;

	if(I>10)
	{
		I=10;
		printf("ERROR: I>10\n");
	}
	if(I<-10)
	{
		I=-10;
		printf("ERROR: I<-10\n");
	}

	double dv;
	double dw;

	dv= (discretization_time)*(v - (v*v*v)/3.0 -w + I);
	dw= (discretization_time)*(1.0/tal)*(v + a -b*w);

	v+=dv;
	w+=dw;

	return v;
}
