#include <iostream>
#include "SLList.h"
#include "DLList.h"
#include "Stack.h"
#include "Deque.h"
#include "Queue.h"

int main()
{
    //------------------------------------------------------------------
    // Q4: Stack tests
    //------------------------------------------------------------------
    std::cout << "=== Q4: Stack ===" << std::endl;

    Stack< int > stack;

    stack.push(5);
    std::cout << stack << std::endl;       // [5]

    stack.push(6);
    std::cout << stack << std::endl;       // [6, 5]

    stack.push(4);
    std::cout << stack << std::endl;       // [4, 6, 5]

    stack.pop();
    std::cout << stack << std::endl;       // [6, 5]

    int x = stack.top();
    std::cout << x << std::endl;           // 6

    stack.top() = 7;
    std::cout << stack << std::endl;       // [7, 5]

    int sz = stack.size();
    std::cout << sz << std::endl;          // 2

    bool b = stack.is_empty();
    std::cout << b << std::endl;           // 0

    stack.clear();
    std::cout << stack.size() << std::endl;// 0

    // pop on empty stack throws UnderflowError
    try
    {
        stack.pop();
    }
    catch (UnderflowError & e)
    {
        std::cout << "UnderflowError caught" << std::endl;
    }

    //------------------------------------------------------------------
    // Q5: Deque tests
    //------------------------------------------------------------------
    std::cout << "\n=== Q5: Deque ===" << std::endl;

    Deque< int > deque;

    deque.push_front(5);
    std::cout << deque << std::endl;       // [5]

    deque.push_back(6);
    std::cout << deque << std::endl;       // [5, 6]

    x = deque.front();
    std::cout << x << std::endl;           // 5

    deque.front() = 4;
    std::cout << deque << std::endl;       // [4, 6]

    int y = deque.back();
    std::cout << y << std::endl;           // 6

    deque.back() = 7;
    std::cout << deque << std::endl;       // [4, 7]

    deque.pop_front();
    std::cout << deque << std::endl;       // [7]

    deque.pop_back();
    std::cout << deque << std::endl;       // []

    sz = deque.size();
    std::cout << sz << std::endl;          // 0

    b = deque.is_empty();
    std::cout << b << std::endl;           // 1

    deque.push_front(1);
    deque.push_front(1);
    deque.push_front(1);
    std::cout << deque << std::endl;       // [1, 1, 1]

    deque.clear();
    std::cout << deque << std::endl;       // []

    // pop on empty deque throws UnderflowError
    try
    {
        deque.pop_front();
    }
    catch (UnderflowError & e)
    {
        std::cout << "UnderflowError caught" << std::endl;
    }

    try
    {
        deque.pop_back();
    }
    catch (UnderflowError & e)
    {
        std::cout << "UnderflowError caught" << std::endl;
    }

    //------------------------------------------------------------------
    // Q6: Queue tests
    //------------------------------------------------------------------
    std::cout << "\n=== Q6: Queue ===" << std::endl;

    Queue< int > queue;

    queue.enqueue(5);
    std::cout << queue << std::endl;       // [5]

    queue.enqueue(6);
    std::cout << queue << std::endl;       // [5, 6]

    x = queue.front();
    std::cout << x << std::endl;           // 5

    queue.front() = 4;
    std::cout << queue << std::endl;       // [4, 6]

    y = queue.back();
    std::cout << y << std::endl;           // 6

    queue.dequeue();
    std::cout << queue << std::endl;       // [6]

    sz = queue.size();
    std::cout << sz << std::endl;          // 1

    queue.clear();
    std::cout << queue << std::endl;       // []

    b = queue.is_empty();
    std::cout << b << std::endl;           // 1

    queue.enqueue(1);
    queue.enqueue(1);
    queue.enqueue(1);
    std::cout << queue << std::endl;       // [1, 1, 1]

    queue.clear();
    std::cout << queue << std::endl;       // []

    // dequeue on empty queue throws UnderflowError
    try
    {
        queue.dequeue();
    }
    catch (UnderflowError & e)
    {
        std::cout << "UnderflowError caught" << std::endl;
    }

    return 0;
}
