#ifndef PHYSICS_H
#define PHYSICS_H


#include <vector>
#include "particle.h"


extern bool gravityEnabled;
extern bool frictionEnabled;

constexpr float GRAVITY_STRENGTH    = 0.3f;
constexpr float FRICTION_DAMPING    = 0.99f;

void applyGravity(Particle* p);
void applyFriction(Particle* p);


#endif
