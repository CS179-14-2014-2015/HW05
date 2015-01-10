#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <stdio.h>
#include <string>
#include <vector>
#include <cstdlib>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;


SDL_Window* gWindow = nullptr;
SDL_Renderer* renderer = nullptr;

// Class Declaration
class Ball
{
public:
  static const int bRadius = 10;
  int bPosX, bPosY;
  int velX, velY;

  Ball();
  void collisionDetection(Ball* );
  double distanceSquared( int , int , int , int  );
  void render();
  void move();
  ~Ball();

};

class BallGroup
{
  public:
   static const int ballAmount = 50;
   std::vector<Ball> BallGroupContainer;

   BallGroup();
   void render();
   void move();
   void collisionDetection();
   ~BallGroup();
};

// Ball Class Implementation and methods

Ball::Ball()
{
// Starting position
  bPosX = rand() % (SCREEN_WIDTH - bRadius) + bRadius;
  bPosY = rand() % (SCREEN_HEIGHT - bRadius) + bRadius;

// Velocity
  velX = rand() % 9 + 1;
  velY = rand() % 9 + 1;;
}


void Ball::collisionDetection(Ball* otherBall)
{
  int totalRadiusSquared = this->bRadius + otherBall->bRadius;
  totalRadiusSquared *= totalRadiusSquared;

  if(distanceSquared(this->bPosX, this->bPosY, otherBall->bPosX, otherBall->bPosY) < totalRadiusSquared)
  {

  }

}

void Ball::move(){

  if ((bPosX <= 0+bRadius) || (bPosX >= SCREEN_WIDTH-bRadius))
  {
    velX *= -1;
  }
  if ((bPosY <= 0+bRadius) || (bPosY >= SCREEN_HEIGHT-bRadius))
  {
    velY *= -1;
  }
  bPosX += velX;
  bPosY += velY;
}

double Ball::distanceSquared( int x1, int y1, int x2, int y2 )
{
  int deltaX = x2 - x1;
  int deltaY = y2 - y1;
  return deltaX*deltaX + deltaY*deltaY;
}

void Ball::render()
{
  filledCircleRGBA(renderer, bPosX, bPosY, bRadius, 255, 255, 255, 255);
}

Ball::~Ball(){}

// BallGroup Class Implementation and methods
BallGroup::BallGroup(){
 for (int i = 0; i < ballAmount; i++){
  BallGroupContainer.push_back(Ball());
 }
}

void BallGroup::move(){
 for (auto &x : BallGroupContainer){
  x.move();
 }
}

void BallGroup::render(){
 for (auto &x : BallGroupContainer){
  x.render();
 }
}

void BallGroup::collisionDetection(){
}

BallGroup::~BallGroup(){}

// SDL init(), load(), and close() from LazyFoo Productions
bool init()
{
  bool success = true;

  if(SDL_Init(SDL_INIT_VIDEO) < 0)
  {
    printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
    success = false;
  }
  else
  {
    if(!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
    {
      printf("Warning: Linear texture filtering not enabled!");
    }

    gWindow = SDL_CreateWindow("Pepero", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

    if(gWindow == NULL)
    {
      printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
      success = false;
    }
    else
    {
      renderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

      if(renderer == NULL)
      {
        printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
        success = false;
      }
      else
      {
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
      }
    }
  }

  return success;
}

void close()
{

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(gWindow);
  gWindow = NULL;
  renderer = NULL;

  SDL_Quit();
}


/*
* MAIN
*/


int main(int argc, char* args[])
{
  bool quit = false;
  BallGroup lol;

  if(!init())
  {
    printf("Failed to initialize!\n");
  }
  else
  {
    SDL_Event e;
    while(!quit)
    {
      uint capTimer = SDL_GetTicks();
      lol.move();
      while(SDL_PollEvent(&e) != 0)
      {
        if(e.type == SDL_QUIT)
        {
          quit = true;
        }
      }
// Clear Screen
      SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
      SDL_RenderClear(renderer);

// Render Objects
      lol.render();

// Render other objects
      SDL_RenderPresent(renderer);

    }
  }

  close();
  return 0;
}
