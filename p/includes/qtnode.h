#ifndef QTNODE_H
#define QTNODE_H


#include <vector>
#include "rectangle.h"
#include "particle.h"


const int QT_CAPACITY = 2;


class QTNode
{
  public:
    QTNode(Region boundary);
    ~QTNode();

    //insert particle into node, then subdivide if needed
    bool insert(Particle* p);
    // collect all particles that share a leaf node with others
    void getCollisionPairs(std::vector<std::pair<Particle*, Particle*>> & pairs);
    // remove all particles and children
    void clear();
    void draw();
  private: 
    void subdivide();

    Region boundary_;
    std::vector<Particle*> particles_;
    bool divided_;

    QTNode* nw_;
    QTNode* ne_;
    QTNode* sw_;
    QTNode* se_;
};

#endif
