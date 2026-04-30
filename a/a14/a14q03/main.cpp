/********************
 *
 *  Author : Brysen Landis
 *  File : main.cpp
 *
 *******************/

#include <iostream>
#include "maxheapvalue.h"
#include "maxpriorityqueue.h"

int main()
{
    MaxPriorityQueue< maxheap_value > q;

    q.insert(maxheap_value(5,  "a"));
    q.insert(maxheap_value(9,  "c"));
    q.insert(maxheap_value(7,  "b"));
    q.insert(maxheap_value(3,  "d"));
    q.insert(maxheap_value(11, "e"));
    std::cout << "queue: " << q << '\n';
    std::cout << "size:  " << q.size() << '\n';
    std::cout << "max:   " << q.max()  << '\n';  // <11, e>

    maxheap_value v = q.remove();
    std::cout << "removed: " << v << '\n';       // <11, e>
    std::cout << "queue:   " << q << '\n';
    std::cout << "max:     " << q.max() << '\n'; // <9, c>

    std::cout << "is_empty: " << q.is_empty() << '\n'; // 0

    MaxPriorityQueue< maxheap_value > q2(q);
    std::cout << "copy: " << q2 << '\n';
    std::cout << "equal: " << (q == q2) << '\n'; // 1

    MaxPriorityQueue< maxheap_value > q3;
    q3 = q;
    std::cout << "assigned: " << q3 << '\n';

    q.clear();
    std::cout << "after clear size: " << q.size() << '\n';   // 0
    std::cout << "is_empty: " << q.is_empty() << '\n';       // 1

    // also works with plain ints
    MaxPriorityQueue< int > qi;
    qi.insert(3); qi.insert(1); qi.insert(4); qi.insert(1); qi.insert(5);
    std::cout << "int queue: " << qi << '\n';
    std::cout << "int max:   " << qi.max() << '\n';   // 5
    std::cout << "removed:   " << qi.remove() << '\n'; // 5
    std::cout << "int queue: " << qi << '\n';

    return 0;
}
