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

	//tell if an object touch an area
	static bool isTop(FloatRect const& object, unsigned short const& top = 0);
	static bool isBottom(FloatRect const& object, unsigned short const& height);
	static bool isLeft(FloatRect const& object, unsigned short const& left = 0);
	static bool isRight(FloatRect const& object, unsigned short const& width);
	static bool isOutside(FloatRect const& object, unsigned short const& width, unsigned short const& height,
							 unsigned short const& top = 0, unsigned short const& left = 0);
};

#endif /* TOOLS_H_ */
