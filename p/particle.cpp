#include <iostream> 
#include "raylib.h"
#include "./includes/particle.h"

#define ANSI_RESET "\033[30m"
#define ANSI_RED "\033[31m"
#define ANSI_GREEN "\033[32m"

Particle::~Particle() {}

void Particle::RenderParticle()
{
  DrawCircle(posX_, posY_, rad_, GREEN);
}

void Particle::UpdateParticle(bool flag, std::vector<Particle*> & particles)
{
  
  posX_ += vX_;
  posY_ += vY_;
  
  // check for wall collision
  if (posY_ + rad_ >= 720 || posY_ - rad_ <= 0)
  {
    vY_ *= -1; // set velocity in opposite direction
  }
  if (posX_ + rad_ >= 1280 || posX_ - rad_ <= 0)
  {
    vX_ *= -1;  // set velocity in opposite direction
  }
  
  if (flag) // brute force
  {
    std::cout << ANSI_RED << "[COLLISION]" << ANSI_RESET << " BRUTE FORCE\n";
  }
  else // quadtree
  {
    std::cout << ANSI_GREEN << "[COLLISION]" << ANSI_RESET << " QUAD TREE\n";
  }
}

