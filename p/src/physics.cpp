#include "physics.h"
#include <cmath>


bool gravityEnabled    = false;
bool frictionEnabled   = false;


void applyGravity(Particle* p)
{
    p->set_vY(p->get_vY() + GRAVITY_STRENGTH);
}


void applyFriction(Particle* p)
{
    p->set_vX(p->get_vX() * FRICTION_DAMPING);
    p->set_vY(p->get_vY() * FRICTION_DAMPING);
}




