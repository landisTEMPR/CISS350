#ifndef LINKED_LIST_H
#define LINKED_LIST_H
#include <iostream>

class SLNode
{
public:
    SLNode(int key, SLNode * next = NULL)
        : key_(key), next_(next)
    {}
    int key_;
    SLNode * next_;
};

class SLList
{
public:
    SLList()
        : phead_(NULL)
    {}
    void insert_head(int key);
    void delete_head();
    void insert_tail(int key);
    void delete_tail();
    
    SLNode * phead_;
};

// Free function declarations (NOT member functions)
std::ostream & operator<<(std::ostream & cout, const SLList & n);
std::ostream & operator<<(std::ostream & cout, const SLNode & n);

#endif
