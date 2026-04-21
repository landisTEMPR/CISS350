#ifndef RECTANGLE_H
#define RECTANGLE_H

struct Region
{
  float x, y, w, h;

  Region(float x, float y, float w, float h)
    : x(x), y(y), w(w), h(h) {}

  bool contains(float px, float py) const
  {
    return px >= x && px <= x + w &&
           py >= y && py <= y + h;
  }

  bool intersects(const Region& other) const
  {
    return !(other.x > x + w || other.x + other.w < x ||
             other.y > y + h || other.y + other.h < y);
  }
};

#endif
