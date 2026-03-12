// File : test.cpp
// Author : Brysen Landis

#include <iostream>
#include "SLNode.h"
#include "SLList.h"

int main()
{
    SLNode< int > node(5);
    std::cout << node << std::endl;

    SLNode< int >::debug_printing(false);
    std::cout << node << std::endl;
    SLNode< int >::debug_printing(true);

    std::cout << node.get_key() << std::endl;
    std::cout << node.get_next() << std::endl;
    node.set_key(6);
    SLNode< int > node2(7);
    node.set_next(&node2);

    SLList< int > list;
    std::cout << list << std::endl;

    list.insert_head(5);
    std::cout << list << std::endl;

    list.insert_head(6);
    std::cout << list << std::endl;

    SLList< int >::debug_printing(false);
    SLList< int >::debug_printing(false);

    list.insert_head(3);
    std::cout << list << std::endl;
    list.insert_tail(3);
    std::cout << list << std::endl;
    list.insert_tail(2);
    std::cout << list << std::endl;

    int x;

    x = list.remove_head();
    std::cout << list << std::endl;
    std::cout << x << std::endl;

    x = list.remove_tail();
    std::cout << list << std::endl;
    std::cout << x << std::endl;

    SLNode< int > * p = list.find(5);

    x = list.remove(p);
    std::cout << list << std::endl;
    std::cout << x << std::endl;

    try
    {

        SLNode< int > * p;
        list.remove(p);
    }
    catch (ValueError & e)
    {
        std::cout << "ValueError caught" << std::endl;
        
    }

    list.clear();
    std::cout << list << std::endl;

    list.insert_tail(5);
    list.insert_tail(6);
    list.insert_tail(7);
    list.insert_tail(8);
    list.remove(list.find(5));
    std::cout << list << std::endl;
    list.remove(list.find(8));
    std::cout << list << std::endl;
    list.clear();

    list.insert_tail(5);
    list.insert_tail(6);
    list.insert_tail(7);
    list.insert_tail(6);
    list.remove(6);
    std::cout << list << std::endl;
    try
    {
        list.remove(100);
    }
    catch (ValueError & e)
    {
        std::cout << "ValueError caught" << std::endl;
    }


    list.clear();

    list.insert_tail(5);
    list.insert_tail(6);
    list.insert_tail(7);
    list.insert_tail(6);

    SLList< int > newlist(list);
    std::cout << newlist << std::endl;
    list.insert_tail(8);
    newlist = list;
    std::cout << newlist << std::endl;

    list.clear();
    list.insert_tial(5);
    list.insert_tial(6);
    list.insert_tail(7);
    list.instert_tail(6);


    std::cout << list[0] << std::endl;
    std::cout << list[1] << std::endl;
    std::cout << list[2] << std::endl;
    std::cout << list[3] << std::endl;
    try
    {
        list[4];
    }
    catch (IndexError & e)
    {
        std::cout << "IndexError caught" << std::endl;
    }
    try
    {
        list[-1];
    }
    catch (IndexError & e)
    {
        std::cout << "IndexError caught" << std::endl;
    }

    list.clear();

    list.insert_tail(5);
    list.insert_tail(6);
    list.insert_tail(7);
    list.insert_tail(6);
    std::cout << list.size() << std::endl;
    std::cout << list.is_empty() << std::endl;

    list.clear();
    std::cout << list.is_empty() << std::endl;

    return 0;

}
