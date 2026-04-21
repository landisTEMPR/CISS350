#include "quadtree.h"


QuadTree::QuadTree(float x, float y, float w, float h)
{
  root_ = new QTNode(Region(x, y, w, h));
}


QuadTree::~QuadTree()
{
  delete root_;
}


void QuadTree::insert(Particle* p)
{
  root_->insert(p);
}


std::vector<std::pair<Particle*, Particle*>> QuadTree::getCollisionPairs()
{
  std::vector<std::pair<Particle*, Particle*>> pairs;
  root_->getCollisionPairs(pairs);
  return pairs;
}


void QuadTree::clear()
{
  root_->clear();
}


void QuadTree::draw()
{
  root_->draw();
}
