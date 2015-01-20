#ifndef BOUNCE_H
#define BOUNCE_H

#include <SDL2\SDL.h>
#include "ball.h"
#include "vec.h"

#include <vector>

using namespace std;

class bounce
{
	public:
		bounce(unsigned short num);
		~bounce(){};

		int loop();
		void updateBalls();
		void eventHandler();
		void render();
	private:
		SDL_Window *win;
		SDL_Renderer *ren;
		SDL_Event events;
		bool quit;

		double delta;
		double currentTime;
		double lastTime;
		double timerFps;

		vector<ball> balls;

		vec gravity;
};

#endif