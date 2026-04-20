#include <iostream>
#include <vector>

bool nqueens_bt(int n, std::vector< int > &solution)
{
  if ((int) solution.size() == n)
  {
    return true;
  }
  else 
  {
    int col0 = (int) solution.size();
    for (int r0 = 0; r0 < n; ++r0)
    {
      bool is_valid = true;
      for (int col1 = 0; col1 < col0; ++col1)
      {
        int r1 = solution[col1]; // the queen is at i
        if (r0 == r1 || abs(r0 - r1) == abs(col0 - col1))
        {
          is_valid = false;
          break;
        }
      }
      if (is_valid)
      {
        solution.push_back(r0);
        bool flag = nqueens_bt(n, solution);
        if (flag) { return true; }
        solution.pop_back();
      }
      
    }
  }
}

int main()
{
  int n;
  std::cin >> n;
  std::vector< int > solution;
  nqueens_bt(n, solution);
  bool flag = nqueens_bt(n, solution);
  if (flag)
  {
    std::cout << "SUCCESS\n";
    std::vector<std::vector<int> > m(n, std::vector<int>(n, 0));
    for (int c = 0; c < (int) solution.size(); ++c)
    {
      int r = solution[c];
      m[r][c] = 1;
    }
    for (int r = 0; r < n; ++r)
    {
      std::cout << '|';
      for(int c = 0; c < n; ++c)
      {
        std::cout << m[r][c] ? 'Q' : ' ';
      }
      std::cout << "|\n";
    }
  }
  else
  {
    std::cout << "FAIL\n";
  }

  return 0;
}
