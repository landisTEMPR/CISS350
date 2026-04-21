#include "constants.h"
#include <cmath>
#include <collision.h>


int g_collisionCount = 0;


void resolveCollision(Particle* a, Particle* b)
{
  float dx = b->get_posX() - a->get_posX();
  float dy = b->get_posY() - a->get_posY();
  float dist2 = dx * dx + dy * dy;
  float minDist = a->get_rad() + b->get_rad();

  if (dist2 >= minDist * minDist || dist2 <= 0) { return; }

  g_collisionCount++;

  // find neighbors
  a->set_neighbors(a->get_neighbors() + 1);
  b->set_neighbors(b->get_neighbors() + 1);

  float dist = sqrt(dist2);
  float nx = dx / dist;
  float ny = dy / dist;

  // separate overlapping particles
  float overlap = (minDist - dist) * 0.5f;
  a->set_posX(a->get_posX() - nx * overlap);
  a->set_posY(a->get_posY() - ny * overlap);
  b->set_posX(b->get_posX() + nx * overlap);
  b->set_posY(b->get_posY() + ny * overlap);

  // clamp both back inside walls
  a->set_posX(fmax(a->get_rad(), fmin(WIN_WIDTH - a->get_rad(), a->get_posX())));
  a->set_posY(fmax(a->get_rad(), fmin(WIN_HEIGHT  - a->get_rad(), a->get_posY())));
  b->set_posX(fmax(b->get_rad(), fmin(WIN_WIDTH - b->get_rad(), b->get_posX())));
  b->set_posY(fmax(b->get_rad(), fmin(WIN_HEIGHT  - b->get_rad(), b->get_posY())));

  // elastic collision - decompose into normal and tangent
  float tx = -ny, ty = nx;
  float v1n = a->get_vX() * nx + a->get_vY() * ny;
  float v2n = b->get_vX() * nx + b->get_vY() * ny;

  // only resolve if moving toward each other
  if (v1n - v2n >= 0) return;

  float v1t = a->get_vX() * tx + a->get_vY() * ty;
  float v2t = b->get_vX() * tx + b->get_vY() * ty;

  // swap normal components, tangent components unchanged
  a->set_vX(v2n * nx + v1t * tx);
  a->set_vY(v2n * ny + v1t * ty);
  b->set_vX(v1n * nx + v2t * tx);
  b->set_vY(v1n * ny + v2t * ty);
}

void resolveBruteForce(std::vector<Particle*>& particles)
{
  int size = particles.size();
  for (int i = 0; i < size; i++)
  {
    for (int j = i + 1; j < size; j++)
    {
      resolveCollision(particles[i], particles[j]);
    }
  }
}

void resolveQuadTree(QuadTree& qt)
{
  auto pairs = qt.getCollisionPairs();
  for (auto& pair : pairs)
  {
    resolveCollision(pair.first, pair.second);
  }
}
