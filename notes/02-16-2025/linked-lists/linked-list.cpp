#include <iostream>
#include "linked-list.h"

void SLList::insert_head(int key)  // Fixed: void SLList:: not SLList::void
{
    phead_ = new SLNode(key, phead_);
}

void SLList::delete_head()  // Fixed: SLList not SSList
{
    if (phead_ == NULL)
    {
        // throw exception
    }
    else
    {
        SLNode * p = phead_;
        phead_ = phead_->next_;
        delete p;
    }
}

void SLList::insert_tail(int key)  // Fixed: void SLList:: and SLList not SSList
{
    if (phead_ == NULL)
    {
        phead_ = new SLNode(key, phead_);
    }
    else
    {
        SLNode * p = phead_;
        while(p->next_ != NULL)
        {
            p = p->next_;
        }
        p->next_ = new SLNode(key, NULL);
    }
}

void SLList::delete_tail()  // Fixed: void SLList:: and SLList not SSList
{
    if (phead_ == NULL)
    {
        // throw exception
    }
    else if (phead_->next_ == NULL)
    {
        delete phead_;
        phead_ = NULL;
    }
    else
    {
        SLNode * p = phead_;
        while(p->next_->next_ != NULL)
        {
            p = p->next_;
        }
        delete p->next_;
        p->next_ = NULL;
    }
}

// Free functions - NO class scope prefix
std::ostream & operator<<(std::ostream & cout, const SLList & n)
{
    cout << "<SLList " << &n << '\n';
    SLNode * p = n.phead_;
    while (p != NULL)
    {
        std::cout << "    " << (*p) << '\n';
        p = p->next_;
    }
    cout << '>';
    
    return cout;
}

std::ostream & operator<<(std::ostream & cout, const SLNode & n)
{
    cout << "<SLNode " << &n
         << " key:" << n.key_ << ", "
         << "next:" << n.next_
         << '>';
    
    return cout;
}
