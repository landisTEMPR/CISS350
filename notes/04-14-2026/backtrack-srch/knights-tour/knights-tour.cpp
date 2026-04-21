#include <iostream>
#include <vector>
#include <utility>
#include <cmath>
#include <iomanip>

bool backtrack_knights_tour(int n,
                            std::vector< std::vector< int > > & m,
                            std::vector< std::pair< int, int > > & solution)
{
    if (solution.size() == n * n)
    {
        return true;
    }
    else
    {
        if (solution.size() == 0) // this si the first move
        {
            for (int r = 0; r < n; ++r)
            {
                for (int c = 0; c < n; ++c)
                {
                    // put (r,c) into solution
                    std::pair< int, int > p(r, c);
                    solution.push_back(p);
                    m[r][c] = 1;
                    bool flag = backtrack_knights_tour(n, m, solution);
                    if (flag) { return true; }
                    // if received failure, undo my solution
                    solution.pop_back();
                    m[r][c] = 0;
                }
            }
            return false; // tried all options and cannot success
        }
        else // this is not the first move
        {
            int r = solution[solution.size() - 1].first;
            int c = solution[solution.size() - 1].second;
            int change[8][2] = {{-1,+2}, {-2,+1}, {-2,-1}, {-1,-2}, {+1,-2},
                                {+2,-1}, {+2,+1}, {+1,+2}};
            for (int i = 0; i < 8; ++i)
            {
                int r0 = r + change[i][0];
                int c0 = c + change[i][1];
                if (0 <= r0 && r0 < n
                    && 0 <= c0 && c0 < n
                    && m[r0][c0] == 0)
                {
                  std::pair< int, int > p(r0, c0);
                  solution.push_back(p);
                  m[r0][c0] = 1;
                  bool flag = backtrack_knights_tour(n, m, solution);
                  if (flag) { return true; }
                  solution.pop_back();
                  m[r0][c0] = 0;
                }
            }
            return false;
        }
        return false;
    }
}


void print(const std::vector< std::pair< int, int > > & solution)
{
  int size = (int) solution.size();
  int n = (int) sqrt(size);
  std::vector< std::vector< int > > m(n, std::vector< int >(n, 0));
  for (int i = 0; i < size; ++i)
  {
    int r = solution[i].first;
    int c = solution[i].second;
    m[r][c] = i;
  }
  
  for (int c = 0; c < n; ++c)
    {
      std::cout << "+--";
    }
    std::cout << "+\n";
  for (int r = 0; r < n; ++ r)
  {
    std::cout << '|';
    for (int c = 0; c < n; ++ c)
    {
      std::cout << std::setw(2) << m[r][c] << '|';
    }
    std::cout << '\n';
    for (int c = 0; c < n; ++c)
    {
      std::cout << "+--";
    }
    std::cout << "+\n";
  }

}


int main()
{
    int n;
    std::cin >> n;

    // std::vector< int > a(5, 1);
    // std::cout << a.size() << ' ' << a[0] << '\n';
    std::vector< std::vector< int > > m(n, std::vector< int >(n, 0));
    // for (int r = 0; r < n; ++r)
    // {
    //     for (int c = 0; c < n; c++)
    //     {
    //         std::cout << m[r][c] << ' ';
    //     }
    //     std::cout << '\n';
    // }
    
    // std::pair< int, int > p;
    // p.first = 0;
    // p.second = 2;

    std::vector< std::pair< int, int > > solution;
    
    bool flag = backtrack_knights_tour(n, m, solution);
    if (flag)
    {
        std::cout << "SUCCESS\n";
        print(solution);
    }
    else
    {
        std::cout << "FAILURE\n";
    }
                                    
    return 0;
}
