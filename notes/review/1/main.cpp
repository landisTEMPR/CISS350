#include <iostream>

// my attempt **not complete**
// int main()
// {
//     int n = 0;
//     std::cin >> n;

//     for (int i = 0; i < n; ++i)
//     {
//         for (int j = 0; j <= n - 1; ++j)
//         {
//             std::cout << '*';
            
//         }
        
//     }
//     std::cout << '\n';
    
//     return 0;
// }

// liow's thinking
int main()
{
    int n;
    std::cin >> n;
    for (int i = 0; i < n; ++i)
    {
        // std::cout << n - (i + 1) << ' ' << i + 1 << '\n';
        // print spaces
        for (int j = 0; j < n - (i + 1); ++j)
        {
            std::cout << ' ';
        }
        // draw triangle part
        for (int j = 0; j < i + 1; ++j)
        {
            std::cout << (j % 2 == 0 ? '*' : '-');  
        }
        std::cout << '\n';
        
    }

    return 0;
}
