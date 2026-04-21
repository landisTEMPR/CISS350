#include <cmath>
#include "constants.h"
#include "raylib.h"
#include "particle.h"
#include "physics.h"

Particle::~Particle() {}

void Particle::RenderParticle()
{
    Color c;
    if (neighbors_ >= 4) { c = RED; }
    else if (neighbors_ >= 2) { c = ORANGE; }
    else if (neighbors_ >= 1) { c = YELLOW; }
    else { c = GREEN; }
    DrawCircle(posX_, posY_, rad_, c);
}

void Particle::UpdateParticle()
{
    posX_ += vX_;
    posY_ += vY_;

    bool physicsActive = gravityEnabled || frictionEnabled;

    if (physicsActive)
    {
        // soft boundary: push particle back in but don't reflect velocity
        if (posX_ - rad_ <= 0) { posX_ = rad_; }
        if (posX_ + rad_ >= WIN_WIDTH) { posX_ = WIN_WIDTH - rad_; }
        if (posY_ - rad_ <= 0) { posY_ = rad_; }
        if (posY_ + rad_ >= WIN_HEIGHT) { posY_ = WIN_HEIGHT - rad_; }
    }
    else
    {
        // normal wall bouncing
        if (posX_ - rad_ <= 0) { posX_ = rad_; vX_ =  fabs(vX_); }
        if (posX_ + rad_ >= WIN_WIDTH) { posX_ = WIN_WIDTH - rad_; vX_ = -fabs(vX_); }
        if (posY_ - rad_ <= 0) { posY_ = rad_; vY_ =  fabs(vY_); }
        if (posY_ + rad_ >= WIN_HEIGHT) { posY_ = WIN_HEIGHT - rad_; vY_ = -fabs(vY_); }

        // enforce minimum speed only when physics are off
        float speed = sqrt(vX_ * vX_ + vY_ * vY_);
        if (speed < 1.0f && speed > 0.0f)
        {
            vX_ = (vX_ >= 0) ? 1.0f : -1.0f;
            vY_ = (vY_ >= 0) ? 1.0f : -1.0f;
        }
    }
}
