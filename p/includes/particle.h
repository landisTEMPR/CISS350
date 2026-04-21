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
      : posX_(posX), posY_(posY), rad_(rad), vX_(vX), vY_(vY), color_(GREEN)
    {}
    // default ctor
    Particle()
      : posX_(0), posY_(0), rad_(0), vX_(0), vY_(0), color_(GREEN)
    {}
    // dctor
    ~Particle();
    // draws partricle to screen
    void RenderParticle();
    // updates positions, color, and velocity
    void UpdateParticle();
    // getters and setters
    const float get_posX() { return posX_; }
    const float get_posY() { return posY_; }
    const int get_rad() { return rad_; }
    const float get_vX() { return vX_; }
    const float get_vY() { return vY_; }
    Color get_color() { return color_; }
    int get_neighbors() { return neighbors_; }
    void set_posX(float posX) { posX_ = posX; }
    void set_posY(float posY) { posY_ = posY; }
    void set_rad(int rad) { rad_ = rad; }
    void set_vX(float vX) { vX_ = vX; }
    void set_vY(float vY) { vY_ = vY; }
    void set_color(Color c) { color_ = c; }
    void set_neighbors(int n) { neighbors_ = n; }
    void reset_neighbors() { neighbors_ = 0; }

  private:
    float posX_;
    float posY_;
    int rad_;
    float vX_;
    float vY_;
    Color color_;
    int neighbors_;
};

#endif
