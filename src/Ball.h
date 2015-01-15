/*
 * Ball.h
 *
 *  Created on: Jan 10, 2015
 *      Author: guillaume
 */

#ifndef BALL_H_
#define BALL_H_

#include "SFML/Graphics.hpp"

#include "Vector2D.h"

using namespace sf;
using namespace std;


class Ball : public CircleShape {

protected:
	unsigned short mass;	//mass of the ball
	Vector2Df speed;		//speed of the ball

public:
	//Constructor : need the screen dimensions to center it
	Ball(unsigned int const& width,  unsigned int const& height);

	//function that update the position of the ball and handle border collisions.
	void update(const unsigned int &width, const unsigned int &height);

	//handle the elastic collision with the other balls
	void collide(Ball &ball, bool const colorSwap);
	bool isColliding(Ball const& ball) const;

	//used to know if an iterator is pointing at the ball
	bool isEqual(Ball const& ball)const;

	//getters & setters
	unsigned short getMass() const;
	Vector2Df& getSpeed();
	Ball& setSpeed(Vector2Df speed);
};

#endif /* BALL_H_ */
