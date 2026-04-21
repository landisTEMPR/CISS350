#ifndef PARTICLE_H
#define PARTICLE_H

#include <iostream>
#include <vector>
#include "raylib.h"

class Particle
{
  public:
    // ctor
    Particle(float posX, float posY, int rad, int vX, int vY)
      : posX_(posX), posY_(posY), rad_(rad), vX_(vX), vY_(vY)
    {}
    // default ctor
    Particle()
      : posX_(0), posY_(0), rad_(0), vX_(0), vY_(0)
    {}
    // dctor
    ~Particle();
    // draws partricle to screen
    void RenderParticle();
    // updates positions, color, and velocity
    void UpdateParticle(bool flag, std::vector<Particle*> & particles);
    // getters and setters
    const float get_posX() { return posX_; }
    const float get_posY() { return posY_; }
    const int get_rad() { return rad_; }
    const int get_vX() { return vX_; }
    const int get_vY() { return vY_; }
    void set_posX(float posX) { posX_ = posX; }
    void set_posY(float posY) { posY_ = posY; }
    void set_rad(int rad) { rad_ = rad; }
    void set_vX(int vX) { vX_ = vX; }
    void set_vY(int vY) { vY_ = vY; }
    // int set_color() { ; }

  private:
    float posX_;
    float posY_;
    int rad_;
    int vX_;
    int vY_;
    Color color_;
};

#endif
