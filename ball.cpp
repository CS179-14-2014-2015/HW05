#include <cstdlib>
#include <SDL2\SDL.h>

#include "ball.h"
#include "vec.h"

ball::ball()
{
	position.setXCoordinate( (double) (rand() % 1024) );
	position.setYCoordinate( (double) (rand() % 500) );

	velocity.setXCoordinate( (double) (rand() % 100)-100.0 );
	velocity.setYCoordinate( (double) (rand() % 100)-100.0 );

	acceleration.setXCoordinate( 0.0 );
	acceleration.setYCoordinate( 0.0 );

	mass = (double) (rand()%10+1);
	radius = 5;
}

void ball::addForceOnBall( vec f )
{
	f.scaleVector( 1.0 / mass );
	acceleration.addVector( f );
}

void ball::updateBall( const double delta )
{
	velocity.addVector( acceleration, delta );
	acceleration.scaleVector( 0.0 ); 
	position.prevx = position.x;
	position.prevy = position.y;
	position.x += velocity.x * delta;
	position.y += velocity.y * delta;
}

void ball::bounceFromScreen()
{

	bool hitX = false;
	bool hitY = false;

	if ( position.getX() < radius )
	{
		position.setXCoordinate( radius );
		velocity.setXCoordinate( velocity.getX() * -1.0 );

		hitX = true;
	}

	if ( position.getY() < radius )
	{
		position.setYCoordinate( radius );
		velocity.setYCoordinate( velocity.getY() * -1.0 );

		hitY = true;
	}

	if ( position.getX() > 1024 - radius )
	{
		position.setXCoordinate( (double)1024 - radius );
		velocity.setXCoordinate( velocity.getX() * -1.0f );

		hitX = true;
	}

	if ( position.getY() > 500 - radius )
	{
		position.setYCoordinate( (float)500 - radius );
		velocity.setYCoordinate( velocity.getY() * -1.0f );
      
		hitY = true;
	}
}

void ball::collide( ball * other )
{
	vec dist;
	dist.x = position.x - other->position.x;
	dist.y = position.y - other->position.y;

	if ( ( dist.x * dist.x + dist.y * dist.y ) < ( ( radius + other->radius ) * ( radius + other->radius ) ) )
	{
		dist.normalizeVector();
		dist.x *= radius + other->radius;
		dist.y *= radius + other->radius;

		position.x = other->position.x + dist.x;
		position.y = other->position.y + dist.y;

		vec velocityB;
		velocityB.x = velocity.x;
		velocityB.y = velocity.y;

		velocity.x = (velocity.x * (mass - other->mass) + 2 * (other->mass * other->velocity.x)) / (mass + other->mass);
		velocity.y = (velocity.y * (mass - other->mass) + 2 * (other->mass * other->velocity.y)) / (mass + other->mass);

		other->velocity.x = (other->velocity.x * (other->mass - mass) + 2 * (mass * velocityB.x)) / (mass + other->mass);
		other->velocity.y = (other->velocity.y * (other->mass - mass) + 2 * (mass * velocityB.y)) / (mass + other->mass);
	}
}