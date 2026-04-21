#ifndef COLLISION_H
#define COLLISION_H


#include <vector>
#include "particle.h"
#include "quadtree.h"

extern int g_collisionCount;

// resolve collisions between a pait of particles
void resovleCollision(Particle* a, Particle* b);

// brute force check every pair
void resolveBruteForce(std::vector<Particle*>& particles);

// quadtree only check pairs in same leaf node
void resolveQuadTree(QuadTree& qt);

#endif
