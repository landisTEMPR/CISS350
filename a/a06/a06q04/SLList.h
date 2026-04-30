// File : SLList.h
// Author : Brysen Landis

#ifndef SLLIST_H
#define SLLIST_H

#include <iostream>
#include "SLNode.h"

class IndexError 
{
  public:
    const char * what() const { return "Invalid index"; }
};

class ValueError 
{
  public:
    const char * what() const { return "Invalid value"; }
};

template < typename T >
class SLList
{
public:
    SLList()
        : phead_(NULL)
    {}

    SLList(const SLList & rhs)
        : phead_(NULL)
    {
        SLNode<T> * curr = rhs.phead_;
        SLNode<T> * tail = NULL;
        while (curr != NULL)
        {
            SLNode<T> * newnode = new SLNode<T>(curr->get_key());
            if (tail == NULL) phead_ = newnode;
            else              tail->set_next(newnode);
            tail = newnode;               // advance tail every iteration
            curr = curr->get_next();      // advance curr every iteration
        }
    }

    SLList & operator=(const SLList & rhs)
    {
        if (this != &rhs)
        {
            clear();
            SLNode<T> * curr = rhs.phead_;
            SLNode<T> * tail = NULL;
            while (curr != NULL)
            {
                SLNode<T> * newnode = new SLNode<T>(curr->get_key());
                if (tail == NULL) phead_ = newnode;
                else              tail->set_next(newnode);
                tail = newnode;
                curr = curr->get_next();
            }
        }
        return *this;
    }

    ~SLList()
    {
        clear();
    }

    static bool debug_printing() { return debug_printing_; }
    static void debug_printing(bool b) { debug_printing_ = b; }

    void insert_head(const T & key)
    {
        phead_ = new SLNode<T>(key, phead_);
    }

    void insert_tail(const T & key)
    {
        SLNode<T> * newnode = new SLNode<T>(key);
        if (phead_ == NULL) { phead_ = newnode; return; }
        SLNode<T> * curr = phead_;
        while (curr->get_next() != NULL)
            curr = curr->get_next();      // advance first, THEN set next
        curr->set_next(newnode);
    }

    void insert_before(SLNode<T> * p, const T & key)
    {
        if (phead_ == NULL || p == NULL) throw ValueError();
        if (phead_ == p) { insert_head(key); return; }
        SLNode<T> * curr = phead_;
        while (curr->get_next() != NULL && curr->get_next() != p)
            curr = curr->get_next();
        if (curr->get_next() == NULL) throw ValueError();
        curr->set_next(new SLNode<T>(key, p));  // insert before p
    }

    void insert_after(SLNode<T> * p, const T & key)
    {
        if (p == NULL) throw ValueError();
        p->set_next(new SLNode<T>(key, p->get_next()));
    }

    T remove_head()
    {
        if (phead_ == NULL) throw ValueError();
        SLNode<T> * temp = phead_;
        T val = temp->get_key();
        phead_ = phead_->get_next();
        delete temp;
        return val;
    }

    T remove_tail()
    {
        if (phead_ == NULL) throw ValueError();
        if (phead_->get_next() == NULL)
        {
            T val = phead_->get_key();
            delete phead_;
            phead_ = NULL;
            return val;
        }
        SLNode<T> * curr = phead_;
        while (curr->get_next()->get_next() != NULL)
            curr = curr->get_next();
        T val = curr->get_next()->get_key();
        delete curr->get_next();
        curr->set_next(NULL);
        return val;
    }

    T remove(SLNode<T> * p)
    {
        if (phead_ == NULL || p == NULL) throw ValueError();
        if (phead_ == p) return remove_head();
        SLNode<T> * curr = phead_;
        while (curr->get_next() != NULL && curr->get_next() != p)
            curr = curr->get_next();
        if (curr->get_next() == NULL) throw ValueError();
        T val = p->get_key();
        curr->set_next(p->get_next());
        delete p;
        return val;
    }

    void remove(const T & key)
    {
        SLNode<T> * p = find(key);
        if (p == NULL) throw ValueError();
        remove(p);
    }

    void clear()
    {
        while (phead_ != NULL) remove_head();
    }

    SLNode<T> * find(const T & key) const
    {
        SLNode<T> * curr = phead_;
        while (curr != NULL)
        {
            if (curr->get_key() == key) return curr;
            curr = curr->get_next();
        }
        return NULL;
    }

    T & operator[](int i)
    {
        if (i < 0) throw IndexError();
        SLNode<T> * curr = phead_;
        int idx = 0;
        while (curr != NULL)
        {
            if (idx == i) return curr->get_key();
            curr = curr->get_next();
            ++idx;
        }
        throw IndexError();
    }

    T & front()
    {
        if (phead_ == NULL) throw ValueError();
        return phead_->get_key();
    }

    T & back()
    {
        if (phead_ == NULL) throw ValueError();
        SLNode<T> * curr = phead_;
        while (curr->get_next() != NULL)
            curr = curr->get_next();
        return curr->get_key();
    }

    int size() const
    {
        int count = 0;
        SLNode<T> * curr = phead_;
        while (curr != NULL) { ++count; curr = curr->get_next(); }
        return count;
    }

    bool is_empty() const { return phead_ == NULL; }

    bool operator==(const SLList & rhs) const
    {
        SLNode<T> * a = phead_, * b = rhs.phead_;
        while (a != NULL && b != NULL)    // && not %%
        {
            if (a->get_key() != b->get_key()) return false;
            a = a->get_next(); b = b->get_next();
        }
        return (a == NULL && b == NULL);
    }

    bool operator!=(const SLList & rhs) const { return !(*this == rhs); }

    friend std::ostream & operator<<(std::ostream & cout, const SLList & list)
    {
        if (debug_printing_)
        {
            cout << "\n<SLList " << &list << " phead:" << list.phead_ << "\n";
            SLNode<T> * curr = list.phead_;
            while (curr != NULL)
            {
                cout << *curr << "\n";
                curr = curr->get_next();
            }
            cout << ">";
        }
        else
        {
            cout << "[";
            SLNode<T> * curr = list.phead_;
            std::string delim = "";
            while (curr != NULL)
            {
                cout << delim << curr->get_key();
                delim = ", ";
                curr = curr->get_next();
            }
            cout << "]";
        }
        return cout;
    }

private:
    SLNode<T> * phead_;
    inline static bool debug_printing_ = false;
};

#endif
