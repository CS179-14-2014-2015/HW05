/*
 * Tools.cpp
 *
 *  Created on: Dec 15, 2014
 *      Author: guillaume
 */

#include "Tools.h"

bool Tools::isTop(FloatRect  const& object, const unsigned short & top) {return object.top <= top;}

bool Tools::isLeft(const FloatRect& object, const unsigned short & left) {return object.left <= left;}

bool Tools::isBottom(const FloatRect& object, const unsigned short & height) {
	return object.top + object.width >= height;
}
bool Tools::isRight(const FloatRect& object, const unsigned short & width) {
	return object.left + object .width >= width;
}

bool Tools::isOutside(const FloatRect& object, const unsigned short & width, const unsigned short & height,
						 const unsigned short & top,	const unsigned short & left) {
	return isTop(object, top) || isLeft(object, left) || isRight(object, width) || isBottom(object, height);
}
