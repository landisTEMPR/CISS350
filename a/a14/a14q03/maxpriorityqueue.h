#ifndef MAXPRIORITYQUEUE_H
#define MAXPRIORITYQUEUE_H

#include <vector>
#include <stdexcept>
#include "maxheap.h"

template < typename T >
class MaxPriorityQueue
{
public:
    MaxPriorityQueue() {}

    MaxPriorityQueue(const MaxPriorityQueue< T > & other)
        : heap_(other.heap_)
    {}

    MaxPriorityQueue< T > & operator=(const MaxPriorityQueue< T > & other)
    {
        if (this != &other) heap_ = other.heap_;
        return *this;
    }

    void insert(const T & value)
    {
        maxheap_insert(heap_, value);
    }

    T remove()
    {
        return maxheap_delete(heap_);
    }

    const T & max() const
    {
        return maxheap_max(heap_);
    }

    void clear()
    {
        heap_.clear();
    }

    int size() const
    {
        return (int)heap_.size();
    }

    bool is_empty() const
    {
        return heap_.empty();
    }

    bool operator==(const MaxPriorityQueue< T > & other) const
    {
        return heap_ == other.heap_;
    }

    bool operator!=(const MaxPriorityQueue< T > & other) const
    {
        return !(*this == other);
    }

    friend std::ostream & operator<<(std::ostream & cout,
                                     const MaxPriorityQueue< T > & q)
    {
        cout << q.heap_;
        return cout;
    }

private:
    std::vector< T > heap_;
};

#endif
