#ifndef DLLIST_H
#define DLLIST_H

#include <iostream>
#include "DLNode.h"

class IndexError {};
class ValueError {};

template < typename T >
class DLList
{
  public:
    DLList()
    {
      head_.set_next(&tail_);
      tail_.set_prev(&head_);
    }


    DLList( const DLList & other)
    {
      head_.set_next(&tail_);
      tail_.set_prev(&head_);
      DLNode<T> * p = other.head_.get_next();
      while (p != &other.tail_)
      {
        insert_tail(p->get_key());
        p = p->get_next();
      }
    }


    ~DLList()
    {
      clear();
    }


    DLList & operator=(const DLList & other)
    {
      if (this != &other)
      {
        clear();
        DLNode<T> * p = other.head_.get_next();
        while (p != &other.tail_)
        {
          insert_tail(p->get_key());
          p = p->get_next();
        }
      }
      return *this;
    }


    void insert_head(const T & key)
    {
      DLNode<T> * node = new DLNode<T>(key, &head_, head_.get_next());
      head_.get_next()->set_prev(node);
      head_.set_next(node);
    }

    
    void insert_tail(const T & key)
    {
      DLNode<T> * node = new DLNode<T>(key, tail_.get_prev(), &tail_);
      tail_.get_prev()->set_next(node);
      tail_.set_prev(node);
    }


    void insert_before(DLNode<T> * p, const T & key)
    {
      DLNode<T> * node = new DLNode<T>(key, p->get_prev(), p);
      p->get_prev()->set_next(node);
      p->set_prev(node);
    }
    
    
    void insert_after(DLNode<T> * p, const T & key)
    {
      DLNode<T> * node = new DLNode<T>(key, p, p->get_next());
      p->get_next()->set_prev(node);
      p->set_next(node);
    }


    T remove_head()
    {
      if (is_empty()) { throw ValueError(); }
      DLNode<T> * node = head_.get_next();
      T key = node->get_key();
      head_.set_next(node->get_next());
      node->get_next()->set_prev(&head_);
      delete node;
      return key;
    }


    T remove_tail()
    {
      if (is_empty()) { throw ValueError(); }
      DLNode<T> * node = tail_.get_prev();
      T key = node->get_key();
      tail_.set_prev(node->get_prev());
      node->get_prev()->set_next(&tail_);
      delete node;
      return key;
    }


    T remove(DLNode<T> * p)
    {
      DLNode<T> * cur = head_.get_next();
      while (cur != &tail_)
      {
        if (cur == p)
        {
          T key = p->get_key();
          p->get_prev()->set_next(p->get_next());
          p->get_next()->set_prev(p->get_prev());
          delete p;
          return key;
        }
        cur = cur->get_next();
      }
      throw ValueError();
    }


    void remove(const T & key)
    {
      DLNode<T> * p = find(key);
      if (p == NULL) { throw ValueError(); }
      p->get_prev()->set_next(p->get_next());
      p->get_next()->set_prev(p->get_prev());
      delete p;
    }


    DLNode<T> * find(const T & key) const
    {
      DLNode<T> * p = head_.get_next();
      while (p != &tail_)
      {
        if (p->get_key() == key) { return p; }
        p = p->get_next();
      }
      return NULL;
    }


    void clear()
    {
      DLNode<T> * p = head_.get_next();
      while (p != &tail_)
      {
        DLNode<T> * next = p->get_next();
        delete p;
        p = next;
      }
      head_.set_next(&tail_);
      tail_.set_prev(&head_);
    }

    
    T & front()
    {
      if (is_empty()) { throw ValueError(); }
      return head_.get_next()->get_key();
    }

    
    T & back()
    {
      if (is_empty()) { throw ValueError(); }
      return tail_.get_prev()->get_key();
    }


    T & operator[](int i)
    {
      if (i < 0) { throw IndexError(); }
      DLNode<T> * p = head_.get_next();
      int idx = 0;
      while (p != &tail_)
      {
        if (idx == i) { return p->get_key(); }
        p = p->get_next();
        ++idx;
      }
      throw IndexError();
    }

    
    const T & operator[](int i) const
    {
      if (i < 0) { throw IndexError(); }
      DLNode<T> * p = head_.get_next();
      int idx = 0;
      while (p != &tail_)
      {
        if (idx == i) { return p->get_key(); }
        p = p->get_next();
        ++idx;
      }
      throw IndexError();
    }


    int size() const
    {
      int count = 0;
      DLNode<T> * p = head_.get_next();
      while (p != &tail_) { ++count; p = p->get_next(); }
      return count;
    }

    
    bool is_empty() const
    {
      return head_.get_next() == &tail_;
    }


    bool operator==(const DLList & other) const
    {
      DLNode<T> * a = head_.get_next();
      DLNode<T> * b = other.head_.get_next();
      while (a != &tail_ && b != &other.tail_)
      {
        if (a->get_key() != b->get_key()) { return false; }
        a = a->get_next();
        b = b->get_next();
      }
      return (a == &tail_ && b == &other.tail_);
    }


    bool operator!=(const DLList & other) const
    {
      return !(*this == other);
    }

  private:
    DLNode<T> head_;
    DLNode<T> tail_;

    template <typename U>
      friend std::ostream & operator<<(std::ostream &, const DLList<U> &);
};

template < typename T >
std::ostream & operator<<(std::ostream & cout, const DLList<T> & list)
{
    cout << '[';
    DLNode<T> * p = list.head_.get_next();
    std::string delim = "";
    while (p != &list.tail_)
    {
        cout << delim << p->get_key();
        delim = ", ";
        p = p->get_next();
    }
    cout << ']';
    return cout;
}

#endif
