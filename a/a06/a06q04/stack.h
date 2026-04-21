#ifndef STACK_H
#define STACK_H

#include <iostream>
#include "SLList.h"

class UnderflowError {};

template < typename T>
class Stack
{
  public:
    void push(const T & x)
    {
      list_.insert_head(x);
    }

    T pop()
    {
      if (list_.is_empty()) { throw UnderflowError(); }
      return list_.remove_head();
    }

    T & top()
    {
      if (list_.is_empty()) { throw UnderflowError(); }
      return list_.front();
    }

    const T & top() const
    {
      if (list_.is_empty()) { throw UnderflowError(); }
      return list_.front();
    }

    int size() const { return list_.size(); }

    bool is_empty() const { return list_.is_empty(); }

    void clear() { list_.clear(); }

    template < typename U>
      friend std::ostream & operator<<(std::ostream & cout, const Stack< U > & s);

  private:
    SLList< T > list_;
};

template < typename T >
std::ostream & operator<<(std::ostream & cout, const Stack< T > & s)
{
  cout << s.list_;
  return cout;
}

#endif
