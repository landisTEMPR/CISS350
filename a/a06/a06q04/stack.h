#ifndef STACK_H
#define STACK_H

#include "SLList.h"

class UnderflowError
{};

template < typename T >
class Stack
{
public:
    // default constructor - empty stack
    Stack()
    {}

    // push: insert at head (head = top of stack)
    void push(const T & x)
    {
        list_.insert_head(x);
    }

    // pop: remove from head, throw UnderflowError if empty
    void pop()
    {
        if (list_.is_empty())
            throw UnderflowError();
        list_.remove_head();
    }

    // top: return reference to head key (top of stack)
    T & top()
    {
        if (list_.is_empty())
            throw UnderflowError();
        return list_.front();
    }

    const T & top() const
    {
        if (list_.is_empty())
            throw UnderflowError();
        return list_.front();
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

    // print: front of list is top of stack
    friend std::ostream & operator<<(std::ostream & cout,
                                     const Stack< T > & s)
    {
        cout << s.list_;
        return cout;
    }

private:
    SLList< T > list_;
};

#endif
