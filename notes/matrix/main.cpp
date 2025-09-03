#include <iostream>
#include "Mat.h"

int main()
{
    Mat m(3, 4);
    std::cout << m << '\n';
    std::cout << m.nrows() << '\n';
    std::cout << m.ncols() << '\n';
    
    return 0;
}f
