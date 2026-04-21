#include "qtnode.h"


QTNode::QTNode(Region boundary)
  : boundary_(boundary), divided_(false), 
    nw_(nullptr), ne_(nullptr), sw_(nullptr), se_(nullptr)
{}


QTNode::~QTNode()
{
  clear();
}


void QTNode::subdivide()
{
  float x = boundary_.x;
  float y = boundary_.y;
  float hw = boundary_.w / 2.0f;
  float hh = boundary_.h / 2.0f;

  nw_ = new QTNode(Region(x, y, hw, hh));
  ne_ = new QTNode(Region(x + hw, y, hw, hh));
  sw_ = new QTNode(Region(x, y + hh, hw, hh));
  se_ = new QTNode(Region(x + hw, y + hh, hw, hh));

  divided_ = true;

  // push existing particles down into children
  for (Particle* p : particles_)
  {
    if (!nw_->insert(p) && !ne_->insert(p) &&
        !sw_->insert(p) && !se_->insert(p))
    {
      // particle sits on a boundary
    }
  }
  particles_.clear();
}


bool QTNode::insert(Particle* p)
{
  // reject if outside this node's region
  if (!boundary_.contains(p->get_posX(), p->get_posY()))
  {
    return false;
  }
  if (!divided_)
  {
    if ((int)particles_.size() < QT_CAPACITY)
    {
      particles_.push_back(p);
      return true;
    }
    else 
    {
      subdivide();
    }
  }

  if (nw_->insert(p)) { return true; }
  if (ne_->insert(p)) { return true; }
  if (sw_->insert(p)) { return true; }
  if (se_->insert(p)) { return true; }

  particles_.push_back(p);
  return true;
}


void QTNode::getCollisionPairs(std::vector<std::pair<Particle*, Particle*>>& pairs)
{
  if (!divided_)
  {
    for (int i = 0; i < (int)particles_.size(); i++)
    {
      for (int j = i + 1; j < (int)particles_.size(); j++)
      {
        pairs.push_back({particles_[i], particles_[j]});
      }
    }
    return;
  }

  // recursive into children
  if (nw_) { nw_->getCollisionPairs(pairs); }
  if (ne_) { ne_->getCollisionPairs(pairs); }
  if (sw_) { sw_->getCollisionPairs(pairs); }
  if (se_) { se_->getCollisionPairs(pairs); }
}


void QTNode::clear()
{
  particles_.clear();
  divided_ = false;
  delete nw_; nw_ = nullptr;
  delete ne_; ne_ = nullptr;
  delete sw_; sw_ = nullptr;
  delete se_; se_ = nullptr;
}


void QTNode::draw()
{
  // draw this node's boundary
  float x = boundary_.x;
  float y = boundary_.y;
  float w = boundary_.w;
  float h = boundary_.h;

  // draw the 4 edges of this node's boundary
  DrawLine(x, y, x + w, y, LIGHTGRAY);         // top
  DrawLine(x, y + h, x + w, y + h, LIGHTGRAY); // bottom
  DrawLine(x, y, x, y + h, LIGHTGRAY);         // left
  DrawLine(x + w, y, x + w, y + h, LIGHTGRAY); // right

  if (divided_)
  {
    nw_->draw();
    ne_->draw();
    sw_->draw();
    se_->draw();
  }
}
