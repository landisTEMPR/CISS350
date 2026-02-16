#include <iostream>
#include "linked-list.h"


int main()
{
    // create nodes on heap
    SLNode * n5 = new SLNode(5); 
    SLNode * n3 = new SLNode(3); n5->next_ = n3;
    SLNode * n1 = new SLNode(1); n3->next_ = n1;
    SLNode * n7 = new SLNode(7); n1->next_ = n7;

    // SLList list
    // Be able to list.insert_head(42),
    // list.remove_head, list.insert_tail,
    // list.remove_tail.
    
    SLList list;

    // insert ability
    std::cout << "[INSERTION]" << '\n';
    std::cout << list << '\n';
    list.insert_head(0);
    std::cout << list << '\n';
    list.insert_head(1);
    std::cout << list << '\n';
    list.insert_head(3);
    std::cout << list << '\n';
    list.insert_head(5);
    std::cout << list << '\n';

    // delete ability
    std::cout << "[DELETION]" << '\n';
    list.delete_head();
    std::cout << list << '\n';
    list.delete_head();
    list.delete_head();
    std::cout << list << '\n';

    // insert tail
    list.insert_head(5);
    list.insert_head(7);
    list.insert_head(3);
    list.insert_head(9);
    std::cout << "[INSERT TAIL]" << '\n';
    std::cout << list << '\n';
    list.insert_tail(18);
    std::cout << list << '\n';

    // delete tail
    std::cout << "[DELETE TAIL]" << '\n';
    list.delete_tail();
    std::cout << list << '\n';

    return 0;
}
