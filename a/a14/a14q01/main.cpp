/**************************
 *
 *  Author : Brysen Landis
 *  File : main.cpp 
 *  a14q01
 *
 *
 * ************************/


#include <iostream>
#include <vector>
#include "intmaxheap.h"

int main()
{
    int x;
    std::vector< int > heap;

    maxheap_insert(heap, 5);
    std::cout << heap << '\n';          // [5]

    maxheap_insert(heap, 7);
    std::cout << heap << '\n';          // [7, 5]

    maxheap_insert(heap, 9);
    std::cout << heap << '\n';          // [9, 5, 7]

    int a = maxheap_delete(heap);
    std::cout << heap << '\n';          // [7, 5]
    std::cout << "deleted: " << a << '\n';  // 9

    x = maxheap_max(heap);
    std::cout << "max: " << x << '\n'; // 7

    heap[0] = 1;
    std::cout << heap << '\n';          // [1, 5]
    maxheap_heapify_down(heap, 0);
    std::cout << heap << '\n';          // [5, 1]

    heap[1] = 10;
    std::cout << heap << '\n';          // [5, 10]
    maxheap_heapify_up(heap, 1);
    std::cout << heap << '\n';          // [10, 5]

    heap.resize(5);
    heap[0] = 5; heap[1] = 7; heap[2] = 8; heap[3] = 10; heap[4] = 2;
    std::cout << "before build: " << heap << '\n';
    maxheap_build(heap);
    std::cout << "after build:  " << heap << '\n'; // [10, 7, 8, 5, 2]

    heap.resize(5);
    heap[0] = 2; heap[1] = 6; heap[2] = 8; heap[3] = 10; heap[4] = 5;
    std::cout << "before sort: " << heap << '\n';
    maxheap_heapsort(heap);
    std::cout << "after sort:  " << heap << '\n'; // [2, 5, 6, 8, 10]

    return 0;
}
