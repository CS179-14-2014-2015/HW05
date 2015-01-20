#ifdef WIN32
#include <windows.h>
#endif

#include <math.h>
#include "vec.h"

vec::vec()
{
	x = y = 0.0;
	prevx = prevy = 0.0;
}

vec::vec( double a, double b )
{
	x = a;
	prevx = x;
	y = b;
	prevy = y;
}

vec::~vec()
{ }

void vec::addVector( const vec & v, double dt )
{
	if ( dt == 0.0 )
	{
	  prevx = x;
      x += v.getX();
	  prevy = y;
      y += v.getY();
	}
	else
	{
		prevx = x;
		x += v.getX() * dt;
		prevy = y;
		y += v.getY() * dt;
	}
}

void vec::subtractVector( const vec & v )
{
	prevx = x;
	x -= v.getX();
	prevy = y;
	y -= v.getY();
}

void vec::scaleVector( double mul )
{
	prevx = x;
	x *= mul;
	prevy = y;
	y *= mul;
}

void vec::normalizeVector()
{
	double length = getLengthOfVector();
	x /= length;
	y /= length;
}

double vec::getLengthOfVector() const
{
	return sqrt( (x)*(x) + (y)*(y) );
}

double vec::getX() const
{
	return x;
}

double vec::getY() const
{
	return y;
}

double vec::getPrevX() const
{
	return x;
}

double vec::getPrevY() const
{
	return y;
}

void vec::setXCoordinate( double v )
{
	x = v;
}

void vec::setYCoordinate( double v )
{
	y = v;
}