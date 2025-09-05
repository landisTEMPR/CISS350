#include <iostream>
#include "Mat.h"

int main()
{
    Mat m(3, 4);
    std::cout << m << '\n';
    m(0, 0) = 42; // m.operator()(0, 0) = 42;
    // std::cout << m.nrows() << '\n';
    // std::cout << m.ncols() << '\n';

    // p = new Mat(5, 10);

    // ...

    // delete p; destructor of p at memory address
    // returns the memory allocated to the variable
    // back to the heap.
    return 0;
}
