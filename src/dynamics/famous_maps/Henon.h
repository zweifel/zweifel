
#ifndef HENON_H
#define HENON_H

#include"../Dynamics.h"
#include"stdio.h"

class Henon: public Dynamics
{
	public:
		Henon(double a, double b, double x_init, double y_init);
		~Henon();

		double iterate(double input);

		void restingState();

		double a;
		double b;

		double x;
		double y;
};

#endif

