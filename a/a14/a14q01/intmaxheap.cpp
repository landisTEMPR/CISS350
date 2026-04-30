#include "intmaxheap.h"
#include <stdexcept>

std::ostream & operator<<(std::ostream & cout, const std::vector< int > & v)
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

// parent / child index helpers
static int parent(int i)      { return (i - 1) / 2; }
static int left_child(int i)  { return 2 * i + 1; }
static int right_child(int i) { return 2 * i + 2; }

// push node at index i up until heap property is restored
void maxheap_heapify_up(std::vector< int > & h, int i)
{
    while (i > 0 && h[i] > h[parent(i)])
    {
        std::swap(h[i], h[parent(i)]);
        i = parent(i);
    }
}

// push node at index i down until heap property is restored
void maxheap_heapify_down(std::vector< int > & h, int i)
{
    int n = (int)h.size();
    while (true)
    {
        int largest = i;
        int l = left_child(i);
        int r = right_child(i);
        if (l < n && h[l] > h[largest]) largest = l;
        if (r < n && h[r] > h[largest]) largest = r;
        if (largest == i) break;
        std::swap(h[i], h[largest]);
        i = largest;
    }
}

// insert x and restore heap property
void maxheap_insert(std::vector< int > & h, int x)
{
    h.push_back(x);
    maxheap_heapify_up(h, (int)h.size() - 1);
}

// remove and return the max (root), restore heap property
int maxheap_delete(std::vector< int > & h)
{
    if (h.empty()) throw std::underflow_error("heap is empty");
    int max = h[0];
    h[0] = h.back();
    h.pop_back();
    if (!h.empty()) maxheap_heapify_down(h, 0);
    return max;
}

// return the max without removing it
int maxheap_max(const std::vector< int > & h)
{
    if (h.empty()) throw std::underflow_error("heap is empty");
    return h[0];
}

void maxheap_build(std::vector< int > & h)
{
    for (int i = ((int)h.size() / 2) - 1; i >= 0; --i)
        maxheap_heapify_down(h, i);
}

// sort ascending using heap sort
void maxheap_heapsort(std::vector< int > & h)
{
    maxheap_build(h);
    int n = (int)h.size();
    for (int end = n - 1; end > 0; --end)
    {
        std::swap(h[0], h[end]);
        // temporarily shrink view and heapify down
        int saved = (int)h.size();
        // heapify only over [0, end)
        int i = 0;
        while (true)
        {
            int largest = i;
            int l = left_child(i);
            int r = right_child(i);
            if (l < end && h[l] > h[largest]) largest = l;
            if (r < end && h[r] > h[largest]) largest = r;
            if (largest == i) break;
            std::swap(h[i], h[largest]);
            i = largest;
        }
        (void)saved;
    }
}
