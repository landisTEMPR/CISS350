#ifndef MAXHEAP_H
#define MAXHEAP_H

#include <iostream>
#include <vector>
#include <stdexcept>

template < typename T >
std::ostream & operator<<(std::ostream & cout, const std::vector< T > & v)
{
    cout << '[';
    for (int i = 0; i < (int)v.size(); ++i)
    {
        if (i > 0) cout << ", ";
        cout << v[i];
    }
    cout << ']';
    return cout;
}

static inline int mh_parent(int i)      { return (i - 1) / 2; }
static inline int mh_left(int i)        { return 2 * i + 1; }
static inline int mh_right(int i)       { return 2 * i + 2; }

template < typename T >
void maxheap_heapify_up(std::vector< T > & h, int i)
{
    while (i > 0 && h[i] > h[mh_parent(i)])
    {
        std::swap(h[i], h[mh_parent(i)]);
        i = mh_parent(i);
    }
}

template < typename T >
void maxheap_heapify_down(std::vector< T > & h, int i, int n)
{
    while (true)
    {
        int largest = i;
        int l = mh_left(i);
        int r = mh_right(i);
        if (l < n && h[l] > h[largest]) largest = l;
        if (r < n && h[r] > h[largest]) largest = r;
        if (largest == i) break;
        std::swap(h[i], h[largest]);
        i = largest;
    }
}

template < typename T >
void maxheap_heapify_down(std::vector< T > & h, int i)
{
    maxheap_heapify_down(h, i, (int)h.size());
}

template < typename T >
void maxheap_insert(std::vector< T > & h, const T & x)
{
    h.push_back(x);
    maxheap_heapify_up(h, (int)h.size() - 1);
}

template < typename T >
T maxheap_delete(std::vector< T > & h)
{
    if (h.empty()) throw std::underflow_error("heap is empty");
    T max = h[0];
    h[0] = h.back();
    h.pop_back();
    if (!h.empty()) maxheap_heapify_down(h, 0);
    return max;
}

template < typename T >
const T & maxheap_max(const std::vector< T > & h)
{
    if (h.empty()) throw std::underflow_error("heap is empty");
    return h[0];
}

template < typename T >
void maxheap_build(std::vector< T > & h)
{
    for (int i = ((int)h.size() / 2) - 1; i >= 0; --i)
        maxheap_heapify_down(h, i);
}

template < typename T >
void maxheap_heapsort(std::vector< T > & h)
{
    maxheap_build(h);
    for (int end = (int)h.size() - 1; end > 0; --end)
    {
        std::swap(h[0], h[end]);
        maxheap_heapify_down(h, 0, end);
    }
}

#endif
