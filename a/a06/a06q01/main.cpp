// -----------------------------------------------
//
// Author : Brysen Landis
// File : main.cpp 
//
// -----------------------------------------------


#include <iostream>
#include <string>
#include "vector.h"


template < typename T >
std::ostream & operator<<(std::ostream & cout, const vector< T > & v)
{
    std::string delim = "";
    cout << '{';
    for (typename vector< T >::const_iterator p = v.begin();
         p != v.end();
         ++p)
    {
        cout << delim << (*p);
        delim = ", ";
    }
    cout << '}';
    return cout;
}


int main()
{
    std::cout << "=== Basic iterator and const_iterator tests ===" << std::endl;

    vector< int > v(11, 0);  // 11 slots so index 10 is valid  // 10 zeros

    typename vector< int >::iterator p = v.begin();
    typename vector< int >::const_iterator q = v.begin();

    std::cout << v[0] << '\n';   // 0
    std::cout << (*p) << '\n';   // 0
    std::cout << (*q) << '\n';   // 0

    v[0] = 42;
    std::cout << v[0] << '\n';   // 42
    std::cout << (*p) << '\n';   // 42
    std::cout << (*q) << '\n';   // 42

    *p = -1;
    std::cout << v[0] << '\n';   // -1
    std::cout << (*p) << '\n';   // -1
    std::cout << (*q) << '\n';   // -1


    v[1] = 1;
    ++p;
    ++q;
    std::cout << v[1] << '\n';   // 1
    std::cout << (*p) << '\n';   // 1
    std::cout << (*q) << '\n';   // 1

    v[10] = -9999;  // WARNING: out-of-bounds, but assignment requires this
    p = v.end();
    q = v.end();
    std::cout << v[10] << '\n';  // -9999
    std::cout << (*p) << '\n';   // -9999
    std::cout << (*q) << '\n';   // -9999

    v[9] = -9998;
    --p;
    --q;
    std::cout << v[9] << '\n';   // -9998
    std::cout << (*p) << '\n';   // -9998
    std::cout << (*q) << '\n';   // -9998

    *p = -9997;
    std::cout << v[9] << '\n';   // -9997
    std::cout << (*p) << '\n';   // -9997
    std::cout << (*q) << '\n';   // -9997

    std::cout << "\n=== operator<< test ===" << std::endl;
    vector< int > v2(5, 3);
    std::cout << v2 << '\n';     // {3, 3, 3, 3, 3}

    std::cout << "\n=== Extra features (postfix, +=, -=) ===" << std::endl;
    p = v2.begin();
    std::cout << (*(p++)) << '\n';  // 3 (old position)
    std::cout << (*(++p)) << '\n';  // 3 (moved forward again)

    p += 3;
    *p = 42;
    std::cout << v2[5] << '\n';     // Note: out-of-bounds test from assignment

    p -= 2;
    *p = 43;
    std::cout << v2[3] << '\n';     // 43
    std::cout << (*p) << '\n';      // 43

    std::cout << "\n=== Copy constructor and assignment ===" << std::endl;
    vector< int > v3(v2);           // copy constructor
    std::cout << v3 << '\n';

    vector< int > v4(3, 0);
    v4 = v2;                        // assignment operator
    std::cout << v4 << '\n';

    return 0;
}
