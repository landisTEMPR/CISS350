#ifndef QUADTREE_H
#define QUADTREE_H


#include "qtnode.h"
#include "particle.h"
#include <vector>


class QuadTree 
{
  public:
    QuadTree(float x, float y, float w, float h);
    ~QuadTree();

    //insert particle into tree
    void insert(Particle * p);

    // get all collision pairs from leaf nodes
    std::vector<std::pair<Particle *, Particle*>> getCollisionPairs();

    // clear tree for rebuild next frame;
    void clear();

    void draw();

  private:
    QTNode* root_;
};


#endif

