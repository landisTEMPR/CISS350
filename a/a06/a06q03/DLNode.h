#ifndef DLNODE_H
#define DLNODE_H
#include <iostream>
template < typename T >
class DLNode
{
  public:
    DLNode()
      : key_(), next_(NULL), prev_(NULL)
    {}
    DLNode(const T & key, DLNode * prev=NULL, DLNode * next=NULL)
      : key_(key), next_(next), prev_(prev)
    {}
    T & get_key() { return key_; }
    const T & get_key() const { return key_; }
    void set_key(const T & k) { key_ = k; }
    DLNode * get_prev() const { return prev_; }
    void set_prev(DLNode * p) { prev_ = p; }
    DLNode * get_next() const { return next_; }
    void set_next(DLNode * n) { next_ = n; }
  private:
    T key_;
    DLNode * prev_;
    DLNode * next_;
    
    template <typename U>
      friend std::ostream & operator<<(std::ostream & cout, const DLNode<T> & node)
      {
        cout << node.key_;
        return cout;
      }
};
#endif
