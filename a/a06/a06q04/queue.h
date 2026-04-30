#ifndef QUEUE_H
#define QUEUE_H

#include "Deque.h"


template < typename T >
class Queue
{
public:
    // default constructor - empty queue
    Queue()
    {}

    // enqueue: add to back
    void enqueue(const T & x)
    {
        deque_.push_back(x);
    }

    // dequeue: remove from front, throw UnderflowError if empty
    void dequeue()
    {
        if (deque_.is_empty())
            throw UnderflowError();
        deque_.pop_front();
    }

    // front: reference to key at front of queue
    T & front()
    {
        return deque_.front();
    }

    const T & front() const
    {
        return deque_.front();
    }

    // back: reference to key at back of queue
    T & back()
    {
        return deque_.back();
    }

    const T & back() const
    {
        return deque_.back();
    }

    int size() const
    {
        return deque_.size();
    }

    bool is_empty() const
    {
        return deque_.is_empty();
    }

    void clear()
    {
        deque_.clear();
    }

    // print: front first
    friend std::ostream & operator<<(std::ostream & cout,
                                     const Queue< T > & q)
    {
        cout << q.deque_;
        return cout;
    }

private:
    Deque< T > deque_;
};

#endif
