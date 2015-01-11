/*
 * Ball.h
 *
 *  Created on: Jan 10, 2015
 *      Author: guillaume
 */

#ifndef BALL_H_
#define BALL_H_

#include "SFML/Graphics.hpp"
#include <list>

using namespace sf;

class Ball : public CircleShape {

protected:
	unsigned int mass;	//the mass of the ball
	float xSpeed;		//the x component of the ball's speed
	float ySpeed;		//the y component of the ball's speed

public:
	Ball(const unsigned int width, const unsigned int height);
	void update(const unsigned int width, const unsigned int height);
};
#endif /* BALL_H_ */
