
#ifndef INTEGRATE_FIRE_H
#define INTEGRATE_FIRE_H

#include"../Dynamics.h"
#include"stdio.h"

class Integrate_Fire: public Dynamics
{
	public:
		Integrate_Fire(double threshold, double discretization_time);
		~Integrate_Fire();

		double iterate(double input);

		void restingState();

		double v;
		double threshold;
		double discretization_time;

};

#endif

