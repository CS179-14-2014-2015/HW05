/*
 * Ball.cpp
 *
 *  Created on: Jan 10, 2015
 *      Author: guillaume
 */

#include "Ball.h"
#include "Tools.h"

unsigned short Ball::getMass() const {	return mass;}
Vector2Df& Ball::getSpeed()  {return speed;}

bool Ball::isEqual(Ball const &ball) const {
	cout << this << ", " << &ball << endl;
	return this == &ball;
}

bool Ball::isColliding(const Ball& ball) const {
	Vector2Df d = getPosition() - ball.getPosition();
	return d.getMagnitude() <= getRadius() + ball.getRadius();
}

Ball& Ball::setSpeed(Vector2Df speed) {
	this->speed = speed;
	return *this;
}

Ball::Ball(unsigned int const& width,  unsigned int const& height) : CircleShape (10), speed(6, 0){

	//specialization
	short random  = rand() % 3;
	if(random == 0){
		setFillColor(Color::Blue);
		mass = 1;
	}
	if(random == 1){
		setFillColor(Color::Magenta);
		mass = 2;
		setRadius(20);
	}
	if(random == 2){
		setFillColor(Color::Red);
		mass = 3;
		setRadius(30);
	}

	//common settings
	setOrigin(getGlobalBounds().width / 2, getGlobalBounds().height /2);
	setPosition(width / 2, height / 2);
	setOutlineColor(Color::Black);
	setOutlineThickness(2);
	speed.rotate(rand() % 360);
}

void Ball::update(const unsigned int &width, const unsigned int &height) {

	//check border collisions
	if(Tools::isLeft(getGlobalBounds()))
		speed.x = fabs(speed.x);
	if(Tools::isRight(getGlobalBounds(), width))
		speed.x = -fabs(speed.x);
	if(Tools::isTop(getGlobalBounds()))
		speed.y = fabs(speed.y);
	if(Tools::isBottom(getGlobalBounds(), height))
		speed.y = -fabs(speed.y);

	//move the ball
	move(speed);
}

void Ball::collide(Ball& ball, bool const colorSwap) {

		//first we move the ball so that the ball just touched
		Vector2Df ballThis(ball.getPosition() - getPosition());
		float offset = ball.getRadius() + getRadius() - ballThis.getMagnitude();
		ballThis.setMagnitude(offset / 2);
		move(-ballThis);
		ball.move(ballThis);

		//create  collision vectors
		Vector2Df n = (ball.getPosition() - getPosition());	//vector normal to collision surface
		n.normalize();
		Vector2Df t = n.getNormal(); 	//vector tangent to the collision surface

		//compute projections
		float pn1 = speed.dot(n);
		float pt1 = speed.dot(t);
		float pn2 = ball.getSpeed().dot(n);
		float pt2 = ball.getSpeed().dot(t);

		//compute normal velocity
		unsigned short m2 = ball.getMass();
		float coef1 = (pn1 * (mass - m2) + 2 * m2 * pn2) / (mass + m2);
		float coef2 = (pn2 * (m2 - mass) + 2 * mass * pn1) / (mass + m2);

		//final velocities
		Vector2Df n1 = n * coef1;
		Vector2Df t1 = t * pt1;
		Vector2Df n2 = n * coef2;
		Vector2Df t2 = t * pt2;

		//add the tangent and normal component
		speed.x = n1.x + t1.x;
		speed.y = n1.y + t1.y;
		ball.setSpeed(Vector2Df(n2.x + t2.x, n2.y + t2.y));

		//swap the color
		if(colorSwap){
			Color tmp = getFillColor();
			setFillColor(ball.getFillColor());
			ball.setFillColor(tmp);
		}
}
