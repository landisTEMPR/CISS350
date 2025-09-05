#include <iostream>
#include "Mat.h"

int main()
{
    Mat m(3, 4);
    // std::cout << m.nrows() << '\n';
    // std::cout << m.ncols() << '\n';
    m(0, 0) = 42; // m.operator()(0, 0) = 42
    std::cout << m << '\n';
    

    Mat n(m); // Mat n = m;
    n(1, 0) = -1;
    std::cout << n << '\n';
    return 0;
} // m.~Mat()
