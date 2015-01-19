#include <iostream>
#include <time.h>
#include <SDL.h>
#include <gfx/SDL2_gfxPrimitives.h>
#include <vector>
#include <cmath>
//http://wiki.libsdl.org/APIByCategory

using namespace std;

//If damaged by asteroids, there is an invuln period of 2 seconds

//NOT SUPPOSED TO CHANGE, GAME GOES BONKERS
const int FRAMERATE = 60;
const double FRAME_TIME = 1000/FRAMERATE;
const float PI = 3.14159265;

double dt = 0.1;
int windowWidth = 720;
int windowHeight = windowWidth;
int ballSpeed = 5;
int radius = 20;
int maxBalls = 50;


//it will take windowHeight/bulletSpeed frames for the bullet to traverse the screen
//in a second, a bullet travels bulletspeed*FRAMERATE pixels
//we need the last bullet for each wave to be bulletspeed*FRAMERATE*7 pixels above the top border of the screen

struct ball {
	int x,y;
	float vx,vy;
	Uint32 color;
};

vector<ball> balls (maxBalls);

float fRand()
{
	return rand()/(float)RAND_MAX;
}

float signGen()
{
	if (fRand() > 0.5)
	{
		return 1;
	}
	else
	{
		return -1;
	}
}

void ballInit()
{
	float anglePiece = (2*PI)/maxBalls;
	int spawnRadius = (windowWidth - (2*radius))/2;
	for (int i = 0; i < maxBalls; i++)
	{
		balls[i].x = spawnRadius * cos(anglePiece*i) + (windowWidth/2);
		balls[i].y = spawnRadius * sin(anglePiece*i) + (windowHeight/2);
		float direction = (2*PI)*fRand();
		balls[i].vx = signGen()*ballSpeed*cos(direction);
		balls[i].vy = signGen()*ballSpeed*sin(direction);
		balls[i].color = 0xFF000000 | rand() << 16 | rand();
	}
}

void advanceBalls()
{
	for (int i = 0; i < maxBalls; i++)
	{
		balls[i].x += balls[i].vx;
		balls[i].y += balls[i].vy;
	}
}

void checkCollision()
{
	//wall bounce
	for (int j = maxBalls-1; j >= 0; j--)
	{
		if (balls[j].x < radius)
		{
			balls[j].vx *= -1.0000;
			balls[j].x = radius;
		}
		else if(balls[j].x > windowWidth - radius)
		{
			balls[j].vx *= -1.0000;
			balls[j].x = windowWidth - radius;
		}
		if (balls[j].y < radius)
		{
			balls[j].vy *= -1.0000;
			balls[j].y = radius;
		}
		else if (balls[j].y > windowHeight - radius)
		{
			balls[j].vy *= -1.0000;
			balls[j].y = windowHeight - radius;
		}

		//ball bounce
		//j is the point of reference
		for (int i = 0; i < j; i++) //i<j
		{
			const float dx = balls[j].x - balls[i].x, dy = balls[j].y - balls[i].y;
			const float mag2 = dx * dx + dy * dy;
			const float minD = 2*radius;

			if ( mag2 <= minD * minD ) 
			{
				const float mag = sqrt(mag2);
				const float ndx = dx/mag, ndy = dy/mag;

				//int tempx = balls[j].x, tempy = balls[j].y;
				balls[j].x = (minD + 0.00000) * ndx + balls[i].x;
				balls[j].y = (minD + 0.00000) * ndy + balls[i].y;
				//balls[i].x = (minD + 0.00000) * ndx + tempx;
				//balls[i].y = (minD + 0.00000) * ndy + tempy;
			
				const float proj = -2 * (ndx * balls[j].vx + ndy * balls[j].vy);
				const float proj2 = -2 * (ndx * balls[i].vx + ndy * balls[i].vy);
			
				balls[j].vx += proj * ndx;
				balls[j].vy += proj * ndy;
				balls[i].vx += proj2 * ndx;
				balls[i].vy += proj2 * ndy;
			}
		}
	}
}

int main(int argc, char* argv[]) {

	srand(time(NULL));

	if (SDL_Init(SDL_INIT_EVERYTHING) != 0){
		std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
		return 1;
	}

	SDL_Window *win = SDL_CreateWindow("Bouncing Ballz", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, windowWidth, windowHeight, SDL_WINDOW_SHOWN);
	if (win == nullptr){
		std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
		SDL_Quit();
		return 1;
	}

	SDL_Renderer *ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (ren == nullptr){
		SDL_DestroyWindow(win);
		std::cout << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
		SDL_Quit();
		return 1;
	}

	/*SDL_Texture *tex = SDL_CreateTexture(ren, SDL_PIXELFORMAT_UNKNOWN, SDL_TEXTUREACCESS_STATIC, 720, 720);
	if (tex == nullptr){
		std::cout << "SDL_CreateTexture Error: " << SDL_GetError() << std::endl;
		SDL_Quit();
		return 1;
	}*/


	//TEXTURE CREATION HOLLAAAA
	/*SDL_Surface *ship = SDL_LoadBMP("Ship.bmp");
	SDL_Texture *tex = SDL_CreateTextureFromSurface(ren, ship);
	SDL_FreeSurface(ship);

	SDL_Surface *damShip = SDL_LoadBMP("damShip.bmp");
	SDL_Texture *damTex = SDL_CreateTextureFromSurface(ren, damShip);
	SDL_FreeSurface(damShip);

	SDL_Surface *rocks = SDL_LoadBMP("ROCKS.bmp");
	SDL_Texture *ast = SDL_CreateTextureFromSurface(ren, rocks);
	SDL_FreeSurface(rocks);

	SDL_Surface *winScreen = SDL_LoadBMP("winscreen.bmp");
	SDL_Texture *winScreenTex = SDL_CreateTextureFromSurface(ren, winScreen);
	SDL_FreeSurface(winScreen);*/

	bool running = true;

	int frameNo = 0;

	//Uint32 color1 = 0xFF777744, color2 = 0xFF334455;
	
	SDL_ShowCursor(1);
	
	int currentFrame = 0;

	ballInit();

	while (running) {
		int frameTimeStart = SDL_GetTicks();
		SDL_Event ev;
		while(SDL_PollEvent(&ev) != 0) {
			if(ev.type == SDL_QUIT) running = false;
		}
		SDL_RenderClear(ren);
		
		advanceBalls();
		checkCollision();
		//DRAW
		for (int i = 0; i < maxBalls; i++)
		{
			filledCircleColor(ren,balls[i].x,balls[i].y,radius,balls[i].color);
		}

		circleColor(ren,windowWidth,windowHeight,1,0xff000000);
		currentFrame++;
		if (currentFrame%60==0)
		{
			cout << SDL_GetTicks() << endl;
		}
		SDL_RenderPresent(ren);
		
		//DELAY
		if ((FRAME_TIME - (SDL_GetTicks() - frameTimeStart)) > 0)
		{
			SDL_Delay(FRAME_TIME - (SDL_GetTicks() - frameTimeStart));
		}
	}

	//SDL_DestroyTexture(tex);
	SDL_DestroyRenderer(ren);
	SDL_DestroyWindow(win);
	SDL_Quit();
}
