// File : SLNode.h
// Author : Brysen Landis

#ifndef SLNODE_H
#define SLNODE_H

template < typename T >

class SLNode
{
  public:
  SLNode(const T & key, SLNode * next=NULL)
      : key_(key_), next_(next)
    {}
    void print(const Node);
    static debug_printing() const { return debug_printing; }
    static debug_printing(bool b) { debug_printing = b; }
  private:
    inline static bool debug_printing = false; 
    T key_;
    SLNode * next_;
};
 
#endif 
