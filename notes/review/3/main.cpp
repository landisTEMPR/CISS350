#include <iostream>

int * linearsrch(int * start, int * end, int target)
{
    for (int * p = start; p < end; ++p)
    {
        if (*p == target) return p;
    }
    return NULL;
}

int main()
{
    int x[] = {5, 6, 4, 3, 1, 10, 9, 7, 5, 7, 3, 2};
    int * p = linearsrch(&x[2], &x[8], 1);
    std::cout << p << '\n';
}
