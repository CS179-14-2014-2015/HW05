#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <stdio.h>
#include <vector>
#include <cstdlib>
#include <cmath>

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

SDL_Window* gWindow = nullptr;
SDL_Renderer* renderer = nullptr;

// Class Declaration
class Ball
{
 public:

  // Ball dimensions
  double bRadius = 10;
  double bMass = 10;
  double bPosX, bPosY;
  int velX, velY;

  // Unique ID
  const int uid;
  int hitByID = 0;

  Ball();
  void checkBallBoundaries(Ball& );
  void collisionDetection(Ball& );
  void determineCollisionPoint(Ball& );
  double distance( int , int , int , int  );
  void render();
  void move();
  ~Ball();

  private:
     // uid hack
    static int newUID;
    // Ball Boundaries Flag
    bool overlappedBoundary;
    // Collision Points
    int collisionX;
    int collisionY;
    // colorsssss
    int red = rand() % 255;
    int green = rand() % 255;
    int blue = rand() % 255;
};

// Ball UID hack
int Ball::newUID = 0;

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

Ball::Ball(): uid(newUID++)
{
// Starting position
  bPosX = rand() % int(SCREEN_WIDTH/1.5) + bRadius;
  bPosY = rand() % int(SCREEN_HEIGHT/1.5) + bRadius;

// Velocity
  velX = rand() % 20 + 1;
  velY = rand() % 10 + 1;
}

void Ball::checkBallBoundaries(Ball& otherBall)
{
 if (this->bPosX + this->bRadius + otherBall.bRadius > otherBall.bPosX
  && this->bPosX < otherBall.bPosX + this->bRadius + otherBall.bRadius
  && this->bPosY + this->bRadius + otherBall.bRadius > otherBall.bPosY
  && this->bPosY < otherBall.bPosY + this->bRadius + otherBall.bRadius)
 {
     this->overlappedBoundary = true;
     printf("%d", this->overlappedBoundary);
     printf("\n");
 }
 else
 {
     this->overlappedBoundary = false;
     printf("%d", this->overlappedBoundary);
     printf("\n");
 }
}

void Ball::collisionDetection(Ball& otherBall)
{
  this->checkBallBoundaries(otherBall);

  if (this->overlappedBoundary && this->uid != otherBall.uid)
  {
   // Reset flag
   this->overlappedBoundary = false;

   int totalRadius = this->bRadius + otherBall.bRadius;

   if(distance(this->bPosX, this->bPosY, otherBall.bPosX, otherBall.bPosY) < totalRadius)
   {

     /// Computations for "nudging" of colliding balls
     // Computing for vectors and magnitude of this-otherBall (A-B) and otherBall-this (B-A)
     double AB_x = this->bPosX - otherBall.bPosX;
     double AB_y = this->bPosY - otherBall.bPosY;
     double BA_x = otherBall.bPosX - this->bPosX;
     double BA_y = otherBall.bPosY - this->bPosY;
     double AB_mag = std::sqrt(AB_x * AB_x + AB_y * AB_y);
     double BA_mag = std::sqrt(BA_x * BA_x + BA_y * BA_y);

     // Computing for the unit vectors of AB and BA
     double uAB_x = AB_x / AB_mag;
     double uAB_y = AB_y / AB_mag;
     double uBA_x = BA_x / BA_mag;
     double uBA_y = BA_y / BA_mag;

     // Computing for scalar projection
     double sAB = (2 * this->bRadius - AB_mag) / 2 ;
     // Scale unit vectors
     double nAB_x = uAB_x * sAB;
     double nAB_y = uAB_y * sAB;
     double nBA_x = uBA_x * sAB;
     double nBA_y = uBA_y * sAB;

     // Displace balls
     this->bPosX += nAB_x;
     this->bPosY += (nAB_y);
     otherBall.bPosX += (nBA_x);
     otherBall.bPosY += (nBA_y);

//     /// Calculations for getting the resulting velocities after elastic collision Version 2
//     // Compute for the normal vector (OtherBall - this)
//     double nv_x = otherBall.bPosX - this->bPosX;
//     double nv_y = otherBall.bPosY - this->bPosY;
//     double nv_mag = std::sqrt((nv_x * nv_x) + (nv_y * nv_y));
//
//     // Compute for the unit normal vector
//     double unv_x = nv_x / nv_mag;
//     double unv_y = nv_y / nv_mag;
//
//     // Create initial velocity vectors
//     double iv1_x = this->velX;
//     double iv1_y = this->velY;
//     double iv2_x = otherBall.velX;
//     double iv2_y = otherBall.velY;
//
//     // Resolving velocity vectors to normal and tangential unit vectors through dot product
//     double v1n = unv_x * iv1_x + unv_y * iv1_y;
//     double v2n = unv_x * iv2_x + unv_y * iv2_y;
//
//     // computing for new velocities
//     double newV1_x = this->velX - (2 * (v1n - v2n) / (this->bMass + otherBall.bMass)) * otherBall.bMass * unv_x;
//     double newV1_y = this->velY - (2 * (v1n - v2n) / (this->bMass + otherBall.bMass)) * otherBall.bMass * unv_y;
//     double newV2_x = otherBall.velX + (2 * (v1n - v2n) / (this->bMass + otherBall.bMass)) * this->bMass * unv_x;
//     double newV2_y = otherBall.velY + (2 * (v1n - v2n) / (this->bMass + otherBall.bMass)) * this->bMass * unv_y;
//
//     this->velX = newV1_x;
//     this->velY = newV1_y;
//     otherBall.velX = newV2_x;
//     otherBall.velY = newV2_y;

     /// Calculations for getting the resulting velocities after elastic collision Version 1
     // Compute for the normal vector (OtherBall - this)
     double nv_x = otherBall.bPosX - this->bPosX;
     double nv_y = otherBall.bPosY - this->bPosY;
     double nv_mag = std::sqrt((nv_x * nv_x) + (nv_y * nv_y));

     // Compute for the unit normal vector
     double unv_x = nv_x / nv_mag;
     double unv_y = nv_y / nv_mag;

     // Compute for unit tangent
     double utv_x = -unv_y;
     double utv_y = unv_x;

     // Create initial velocity vectors
     double iv1_x = this->velX;
     double iv1_y = this->velY;
     double iv2_x = otherBall.velX;
     double iv2_y = otherBall.velY;

     // Resolving velocity vectors to normal and tangential unit vectors through dot product
     double v1n = unv_x * iv1_x + unv_y * iv1_y;
     double v2n = unv_x * iv2_x + unv_y * iv2_y;
     double v1t = utv_x * iv1_x + utv_y * iv1_y;
     double v2t = utv_x * iv2_x + utv_y * iv2_y;

     // Find the new tangential velocities (after collision)
     double vp1t = v1t;
     double vp2t = v2t;

     // Find the new normal velocities after collision)
     double vp1n = (v1n * (this->bMass - otherBall.bMass) + (2 * otherBall.bMass * v2n)) / (this->bMass + otherBall.bMass);
     double vp2n = (v2n * (otherBall.bMass - this->bMass) + (2 * this->bMass * v1n)) / (this->bMass + otherBall.bMass);

     // Convert scalar normal and tangential velocities into vectors
     double v_vp1n_x = vp1n * unv_x;
     double v_vp1n_y = vp1n * unv_y;
     double v_vp2n_x = vp2n * unv_x;
     double v_vp2n_y = vp2n * unv_y;

     double v_vp1t_x = vp1t * utv_x;
     double v_vp1t_y = vp1t * utv_y;
     double v_vp2t_x = vp2t * utv_x;
     double v_vp2t_y = vp2t * utv_y;

     // Find the final velocities through the sum of normal and tangential velocities
     this->velX = v_vp2n_x + v_vp2t_x;
     this->velY = v_vp2n_y + v_vp2t_y;
     otherBall.velX = v_vp1n_x + v_vp1t_x;
     otherBall.velY = v_vp1n_y + v_vp1t_y;
   }
  }
}

void Ball::determineCollisionPoint(Ball& otherBall)
{
 this->collisionX =
 ((this->bPosX * otherBall.bRadius) + (otherBall.bPosX * this->bRadius))
 / (this->bRadius + otherBall.bRadius);

 this->collisionY =
 ((this->bPosY * otherBall.bRadius) + (otherBall.bPosY * this->bRadius))
 / (this->bRadius + otherBall.bRadius);


}

void Ball::move(){

  if (bPosX <= 0+bRadius)
  {
    this->bPosX = bRadius;
    velX = std::fabs(velX);
  }
  else if  (bPosX >= SCREEN_WIDTH-bRadius)
  {
    this->bPosX = SCREEN_WIDTH-bRadius;
    velX = -std::fabs(velX);
  }

  else if (bPosY <= 0+bRadius)
  {
    this->bPosY = bRadius;
    velY = std::fabs(velY);
  }
  else if (bPosY >= SCREEN_HEIGHT-bRadius)
  {
    this->bPosY = SCREEN_HEIGHT-bRadius;
    velY = -std::fabs(velY);
  }
  bPosX += velX;
  bPosY += velY;
}

double Ball::distance( int x1, int y1, int x2, int y2 )
{
  int distance = sqrt(
            ((x1 - x2) * (x1 - x2))
          + ((y1 - y2) * (y1 - y2))
           );
  return distance;
}

void Ball::render()
{
  filledCircleRGBA(renderer, bPosX, bPosY, bRadius, red, green, blue, 255);
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
    for (auto &pCircle : BallGroupContainer){
      for(auto &tCircle : BallGroupContainer)
            pCircle.collisionDetection(tCircle);
    }
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
      lol.collisionDetection();
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
      //SDL_Delay(200);
    }
  }
  close();
  return 0;
}
