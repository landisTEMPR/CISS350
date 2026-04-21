#include <iostream> 
#include <cmath>
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
  
  // Wall collision - clamp position AND reverse velocity
  if (posX_ - rad_ <= 0)
  {
    posX_ = rad_;         // push back inside
    vX_ = abs(vX_);      // force moving right
  }
  if (posX_ + rad_ >= 1280)
  {
    posX_ = 1280 - rad_;  // push back inside
    vX_ = -abs(vX_);     // force moving left
  }
  if (posY_ - rad_ <= 0)
  {
    posY_ = rad_;         // push back inside
    vY_ = abs(vY_);      // force moving down
  }
  if (posY_ + rad_ >= 720)
  {
    posY_ = 720 - rad_;   // push back inside
    vY_ = -abs(vY_);     // force moving up
  } 
  
  if (flag) // brute force
  {
    std::cout << ANSI_RED << "[COLLISION]" << ANSI_RESET << " BRUTE FORCE\n";
    for (Particle* other : particles)
    {
      if (other == this) { continue; }

      float dx = other->get_posX() - posX_; // get x distance
      float dy = other->get_posY() - posY_; // get y distance
      // find distance between the two particles
      float dist = sqrt(dx * dx + dy * dy);
      // find minimum distance that determines if collision is true
      float minDist = rad_ + other->get_rad();

      if (dist < minDist && dist > 0)
      {
        // swap velocities
        int tmpVX = vX_;
        int tmpVY = vY_;
        vX_ = other->get_vX();
        vY_ = other->get_vY();
        other->set_vX(tmpVX);
        other->set_vY(tmpVY);

        // push apart so no sticking occurs
        float overlap  = minDist - dist;
        posX_ -= (dx / dist) * (overlap / 2);
        posY_ -= (dy / dist) * (overlap / 2);
      }
    }
  }
  else // quadtree
  {
    std::cout << ANSI_GREEN << "[COLLISION]" << ANSI_RESET << " QUAD TREE\n";
  }
}

