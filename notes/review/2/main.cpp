#include <iostream>
#include <cstdlib>
#include <ctime>

char coin_toss();

int main()
{
    srand((unsigned int) time(NULL));
    int count = 0;
    while (count < 3)
    {
        char coin = coin_toss();
        std::cout << coin << ' ';
        if (coin == 'H')
        {
            ++count;
        }
        else
        {
            count = 0;
        }
        std::cout << count << ' ';
    }
    std::cout << '\n';
}

char coin_toss()
{
    return (rand() % 2 == 0 ? 'H' : 'T');
}
