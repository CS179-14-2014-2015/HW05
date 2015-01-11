/*
 * Tools.h
 *
 *  Created on: Dec 15, 2014
 *      Author: guillaume
 */

#ifndef TOOLS_H_
#define TOOLS_H_

#include <SFML/Graphics.hpp>
#include <cmath>

using namespace sf;

class Tools {

public:

	/*
	 * /!\ We consider that the object passed have their origin centered
	 */


	static bool isTop(Sprite const &sprite);			//tell if a sprite touch the top of the screen
	static bool isBottom(Sprite const &sprite, RenderWindow const &window);		//tell if a sprite touch the bottom of the screen
	static bool isLeft(Sprite const &sprite);		//tell if a sprite touch the left of the screen
	static bool isRight(Sprite const &sprite, RenderWindow const &window);		//tell if a sprite touch the right of the screen
	static bool isOutside(Sprite const &sprite, RenderWindow const &window);		//tell if a sprite touch a border of the screen

	//tell if a shape touch the top of an area
	static bool isTop(Shape const &shape, unsigned int const top);

	//tell if a shape touch the bottom of a limited area
	static bool isBottom(Shape const &shape, unsigned int const bottom);

	//tell if a shape touch the left side of a limited area
	static bool isLeft(Shape const &shape, unsigned int const left);

	//tell if a shape touch the right side of a limited area
	static bool isRight(Shape const &shape, unsigned int const right);

	//return a unit vector for an angle
	static Vector2f vectorFromAngle(int angle);

	//give the norm of a vector
	static float norm(Vector2f a, Vector2f b);

};

#endif /* TOOLS_H_ */
