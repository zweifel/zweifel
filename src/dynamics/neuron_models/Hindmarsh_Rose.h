
#ifndef HINDMARSH_ROSE_H
#define HINDMARSH_ROSE_H

#include"../Dynamics.h"
#include"stdio.h"

class Hindmarsh_Rose: public Dynamics
{
	public:
		//From the wiki: http://en.wikipedia.org/wiki/Hindmarsh-Rose_model
		//
		//Usually the parameter I, which means the current that enters the neuron, is taken as a control parameter. 
		//Other control parameters used often in the literature are a, b or r, 
		//the first two modeling the working of the fast ion channels and the last one the slow ion channels, respectively. 
		//Very frequently, the parameters held fixed are s = 4 and xR = -8/5. 
		//When a or b are fixed the values given are a = 3 and b = 5. 
		//The parameter r is something of the order of 10-3, and I ranges between -10 and 10.
		Hindmarsh_Rose(double a, double b, double r, double s, double xr, double tal);
		~Hindmarsh_Rose();

		double iterate(double input);

		void restingState();

		double a;
		double b;
		double r;
		double s;
		double xr;
		double tal;
		double I;

		double x;
		double y;
		double z;
};

#endif

