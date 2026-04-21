#include <iostream> 
#include <cmath>
#include "raylib.h"
#include "particle.h"


#define ANSI_RESET "\033[0m"
#define ANSI_RED "\033[31m"
#define ANSI_GREEN "\033[32m"


Particle::~Particle() {}


void Particle::RenderParticle()
{
  DrawCircle(posX_, posY_, rad_, GREEN);
}


void Particle::UpdateParticle(bool flag, std::vector<Particle*>& particles, int index)
{
  int size = particles.size();
  posX_ += vX_;
  posY_ += vY_;

  // wall collision
  if (posX_ - rad_ <= 0)    { posX_ = rad_;        vX_ =  fabs(vX_); }
  if (posX_ + rad_ >= 1280) { posX_ = 1280 - rad_; vX_ = -fabs(vX_); }
  if (posY_ - rad_ <= 0)    { posY_ = rad_;        vY_ =  fabs(vY_); }
  if (posY_ + rad_ >= 720)  { posY_ = 720 - rad_;  vY_ = -fabs(vY_); }

  if (flag) // brute force
  {
    for (int i = index + 1; i < size; i++)
    {
      Particle* other = particles[i];
      float dx    = other->get_posX() - posX_;
      float dy    = other->get_posY() - posY_;
      float dist2 = dx * dx + dy * dy;
      float minDist = rad_ + other->get_rad();

      if (dist2 < minDist * minDist && dist2 > 0)
      {
        float dist = sqrt(dist2);
        float nx = dx / dist;
        float ny = dy / dist;

        // separate particles so they no longer overlap
        float overlap = (minDist - dist) * 0.5f;
        posX_ -= nx * overlap;
        posY_ -= ny * overlap;
        other->set_posX(other->get_posX() + nx * overlap);
        other->set_posY(other->get_posY() + ny * overlap);

        // clamp both back inside walls
        posX_ = fmax(rad_, fmin(1280 - rad_, posX_));
        posY_ = fmax(rad_, fmin(720  - rad_, posY_));
        other->set_posX(fmax(rad_, fmin(1280 - rad_, other->get_posX())));
        other->set_posY(fmax(rad_, fmin(720  - rad_, other->get_posY())));

        // elastic collision - equal mass
        // project both velocities onto collision normal
        float v1n = vX_ * nx + vY_ * ny;
        float v2n = other->get_vX() * nx + other->get_vY() * ny;

        // only resolve if moving toward each other
        if (v1n - v2n < 0) continue;

        // tangent components stay the same, swap normal components
        float tx = -ny;
        float ty =  nx;
        float v1t = vX_ * tx + vY_ * ty;
        float v2t = other->get_vX() * tx + other->get_vY() * ty;

        // reconstruct velocities from swapped normals + unchanged tangents
        vX_ = v2n * nx + v1t * tx;
        vY_ = v2n * ny + v1t * ty;
        other->set_vX(v1n * nx + v2t * tx);
        other->set_vY(v1n * ny + v2t * ty);

        // enforce minimum speed on both
        float s1 = sqrt(vX_ * vX_ + vY_ * vY_);
        float s2 = sqrt(other->get_vX() * other->get_vX() + other->get_vY() * other->get_vY());
        if (s1 < 1.0f) { vX_ = (vX_ >= 0) ?  1.0f : -1.0f; vY_ = (vY_ >= 0) ?  1.0f : -1.0f; }
        if (s2 < 1.0f) { other->set_vX(other->get_vX() >= 0 ? 1.0f : -1.0f);
                         other->set_vY(other->get_vY() >= 0 ? 1.0f : -1.0f); }
      }
    }
  }
  else // quadtree
  {
    // coming soon
  }
}
