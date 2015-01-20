#ifndef BALL_H
#define BALL_H

#include "vec.h"

class ball
{
	public:
		ball();
		~ball(){};

		void updateBall(const double dt);
		void bounceFromScreen();
		void collide(ball *otherBall);
		void addForceOnBall(vec f);
			
		double mass;
		int radius;

		vec position;
		vec velocity;
		vec acceleration;
};

#endif