// File : SLList.
// Author : Brysen Landis

#ifndef SLLIST_H
#define SLLIST_H

template < typename T >

class IndexError
{};

class ValueError
{};

template < typename T>
class SSList
{
  public:
    SLList()
        : phead_(NULL)
    {}
  private:
    SLNode < T > * phead_;
};

#endif
