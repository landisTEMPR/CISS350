// File : main.cpp
// Author : Brysen Landis
//
#include <iostream>
#include "DLNode.h"
#include "DLList.h"

int main()
{
    DLList<int> list;
    list.insert_head(5);
    list.insert_head(6);
    list.insert_tail(3);
    std::cout << list << std::endl;  // [6, 5, 3]

    list.remove_head();
    std::cout << list << std::endl;  // [5, 3]

    list.remove_tail();
    std::cout << list << std::endl;  // [5]

    list.clear();
    list.insert_tail(5);
    list.insert_tail(6);
    list.insert_tail(7);
    list.insert_tail(6);

    list.remove(6);
    std::cout << list << std::endl;  // [5, 7, 6]

    std::cout << list[0] << std::endl;  // 5
    std::cout << list.size() << std::endl;  // 3

    DLList<int> list2(list);
    std::cout << list2 << std::endl;  // [5, 7, 6]

    return 0;
}
