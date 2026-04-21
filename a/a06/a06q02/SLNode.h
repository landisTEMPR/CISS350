// File : SLNode.h
// Author : Brysen Landis
#ifndef SLNODE_H
#define SLNODE_H
#include <iostream>
template < typename T >
class SLNode
{
  public:
    SLNode(const T & key, SLNode * next=NULL)
        : key_(key), next_(next)
    {}
    
    int key() const { return key_; }
    SLNode * next() const { return next_; }
    T & get_key() { return key_; }
    const T & get_key() const { return key_; }
    void set_key(const T & k) { key_ = k; }
    SLNode * get_next() const { return next_; }
    void set_next(SLNode * n) { next_ = n; }
    static bool debug_printing() { return debug_printing_; }
    static void debug_printing(bool b) { debug_printing_ = b; }

    friend std::ostream & operator<<(std::ostream & cout, const SLNode<int> & node)
      {
        if (SLNode<int>::debug_printing())
        {
          cout << "<SLNode " << &node
               << " key:" << node.get_key()
               << ", next:" << node.get_next()
               << ">";
        }
        else { cout << node.get_key(); }
        return cout;
      }
    
  private:
    inline static bool debug_printing_ = false; 
    T key_;
    SLNode * next_;
};

#endif
