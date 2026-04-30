/******************
 *
 *  Author : Brysen Landis
 *  File : main.cpp
 *
 * ***************/

#include <iostream>
#include <vector>
#include "maxheapvalue.h"
#include "maxheap.h"

int main()
{
    maxheap_value x;
    std::vector< maxheap_value > heap;

    maxheap_insert(heap, maxheap_value(5, "a"));
    std::cout << heap << '\n';   // [<5, a>]

    maxheap_insert(heap, maxheap_value(7, "b"));
    std::cout << heap << '\n';   // [<7, b>, <5, a>]

    maxheap_insert(heap, maxheap_value(9, "c"));
    std::cout << heap << '\n';   // [<9, c>, <5, a>, <7, b>]

    maxheap_value a = maxheap_delete(heap);
    std::cout << heap << '\n';             // [<7, b>, <5, a>]
    std::cout << "deleted: " << a << '\n'; // <9, c>

    x = maxheap_max(heap);
    std::cout << "max: " << x << '\n';     // <7, b>

    heap[0] = maxheap_value(1, "d");
    std::cout << heap << '\n';             // [<1, d>, <5, a>]
    maxheap_heapify_down(heap, 0);
    std::cout << heap << '\n';             // [<5, a>, <1, d>]

    heap[1] = maxheap_value(10, "e");
    std::cout << heap << '\n';             // [<5, a>, <10, e>]
    maxheap_heapify_up(heap, 1);
    std::cout << heap << '\n';             // [<10, e>, <5, a>]

    // build test
    std::vector< maxheap_value > heap2;
    heap2.push_back(maxheap_value(5,  "a"));
    heap2.push_back(maxheap_value(7,  "b"));
    heap2.push_back(maxheap_value(8,  "c"));
    heap2.push_back(maxheap_value(10, "d"));
    heap2.push_back(maxheap_value(2,  "e"));
    std::cout << "before build: " << heap2 << '\n';
    maxheap_build(heap2);
    std::cout << "after build:  " << heap2 << '\n';

    // heapsort test
    std::vector< maxheap_value > heap3;
    heap3.push_back(maxheap_value(2,  "a"));
    heap3.push_back(maxheap_value(6,  "b"));
    heap3.push_back(maxheap_value(8,  "c"));
    heap3.push_back(maxheap_value(10, "d"));
    heap3.push_back(maxheap_value(5,  "e"));
    std::cout << "before sort: " << heap3 << '\n';
    maxheap_heapsort(heap3);
    std::cout << "after sort:  " << heap3 << '\n'; // ascending by priority

    // also verify with plain ints
    std::vector< int > iheap;
    maxheap_insert(iheap, 5);
    maxheap_insert(iheap, 7);
    maxheap_insert(iheap, 9);
    std::cout << "int heap: " << iheap << '\n';  // [9, 5, 7]

    return 0;
}
