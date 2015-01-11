/*
 * Ball.cpp
 *
 *  Created on: Jan 10, 2015
 *      Author: guillaume
 */

#include "Ball.h"
#include "Tools.h"

Ball::Ball(const unsigned int width, const unsigned int height) : CircleShape (10){

	//default settings
	srand(time(NULL));
	setFillColor(Color::Blue);
	setOrigin(getGlobalBounds().width / 2, getGlobalBounds().height /2);
	setPosition(width / 2, height / 2);
	mass = 10;

	//give the ball a random angle
	Vector2f vector = Tools::vectorFromAngle(rand() % 360);

	//special ball
	if(rand() % 10 == 0) {
		setFillColor(Color::Red);
		mass = 50;
		setRadius(20);
	}

	//give the ball a speed
	short speed = 6;
	xSpeed = vector.x * speed;
	ySpeed = vector.y * speed;
}

void Ball::update(const unsigned int width, const unsigned int height) {

	//check collisions
	if(Tools::isTop(*this, 0) || Tools::isBottom(*this, height))
		ySpeed *= -1;
	if(Tools::isLeft(*this, 0) || Tools::isRight(*this, width))
		xSpeed *= -1;

	//move the ball
	move(xSpeed, ySpeed);
}

