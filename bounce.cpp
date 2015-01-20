#ifdef WIN32
#include <windows.h>
#endif
#include <SDL2\SDL.h>
#include "SDL2_gfxPrimitives.h"

#include <iostream>
#include "bounce.h"
#include "ball.h"
#include "FPS.h"

using namespace std;

FPS fps;

bounce::bounce( unsigned short num )
{
	SDL_Init( SDL_INIT_VIDEO | SDL_INIT_TIMER );

	win = SDL_CreateWindow( "Bounce!", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1024, 500, SDL_WINDOW_SHOWN );
	ren = SDL_CreateRenderer( win, -1, SDL_RENDERER_ACCELERATED ); //| SDL_RENDERER_PRESENTVSYNC );
	quit = false;

	delta = 0.0f;
	currentTime = 0.0f;
	lastTime = 0.0f;
	timerFps = 0.0f;

	for ( unsigned short i = 0; i < num; i++ )
	{
		ball myBall;
		balls.push_back( myBall );
	}

	gravity.x = 0.0f;
	gravity.y = 0.0f;
	//gravity.y = 90.8f;

}
int bounce::loop()
{
	while ( !quit )
	{
		currentTime = (float)SDL_GetTicks();
		delta = ( currentTime - lastTime ) / 1000.0f;
		lastTime = currentTime;
		timerFps = (float)SDL_GetTicks();

		eventHandler();
		updateBalls();
		render();

		SDL_RenderPresent( ren );
		timerFps = SDL_GetTicks() - timerFps;
		if( timerFps < 1000/60 )
		{
			SDL_Delay( 1000/60 - timerFps );
		}
		fps.update();
	}
	return 0;
}
void bounce::eventHandler()
{
	while ( SDL_PollEvent( &events ) )
	{
		if ( events.type == SDL_QUIT )
		{
			quit = true;
		}
	}
}

void bounce::updateBalls()
{
	for ( unsigned short i = 0; i < balls.size(); i++ )
	{
		balls[i].addForceOnBall( gravity );
		balls[i].updateBall( delta );
		balls[i].bounceFromScreen();

		for ( unsigned short j = 0; j < balls.size(); j++ )
		{
			if ( j != i )
			{
				balls[i].collide( &balls[j] );
			}
		}
	}
}

void bounce::render()
{
	for ( unsigned short i = 0; i < balls.size(); i++ )
	{
	    filledCircleRGBA( ren, (int)balls[i].position.prevx, (int)balls[i].position.prevy, balls[i].radius, 0, 0, 0, 255 );
		filledCircleRGBA( ren, (int)balls[i].position.x, (int)balls[i].position.y, balls[i].radius, 255, 255 ,255, 255 );
	}
	
	//fps.update();
}