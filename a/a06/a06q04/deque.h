#ifndef DEQUE_H
#define DEQUE_H

#include "DLList.h"

// UnderflowError is thrown when removing from an empty deque
class UnderflowError
{};

template < typename T >
class Deque
{
public:
    // default constructor - empty deque
    Deque()
    {}

    // push_front: insert at head of underlying list
    void push_front(const T & x)
    {
        list_.insert_head(x);
    }

    // push_back: insert at tail of underlying list
    void push_back(const T & x)
    {
        list_.insert_tail(x);
    }

    // pop_front: remove from head, throw UnderflowError if empty
    void pop_front()
    {
        if (list_.is_empty())
            throw UnderflowError();
        list_.remove_head();
    }

    // pop_back: remove from tail, throw UnderflowError if empty
    void pop_back()
    {
        if (list_.is_empty())
            throw UnderflowError();
        list_.remove_tail();
    }

    // front: reference to key at head
    T & front()
    {
        if (list_.is_empty())
            throw UnderflowError();
        return list_.front();
    }

    const T & front() const
    {
        if (list_.is_empty())
            throw UnderflowError();
        return list_.front();
    }

    // back: reference to key at tail
    T & back()
    {
        if (list_.is_empty())
            throw UnderflowError();
        return list_.back();
    }

    const T & back() const
    {
        if (list_.is_empty())
            throw UnderflowError();
        return list_.back();
    }

    int size() const
    {
        return list_.size();
    }

    bool is_empty() const
    {
        return list_.is_empty();
    }

    void clear()
    {
        list_.clear();
    }

    // print: head is front, tail is back
    friend std::ostream & operator<<(std::ostream & cout,
                                     const Deque< T > & d)
    {
        cout << d.list_;
        return cout;
    }

private:
    DLList< T > list_;
};

#endif
