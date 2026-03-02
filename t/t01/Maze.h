#ifndef MAZE_H
#define MAZE_H

#include <iostream>
#include <vector>

struct Dir
{
    int dirs[4];
    int top;
};

class Cell
{
  public:
    int r, c;
};

class PunchedWall
{
  public:
    Cell c0, c1;
};

class Stack
{
  public:
    Cell data[1024];
    int top;
    Stack()
    {
        top = -1;
    }
    
    void push(Cell c)
    {
        top++;
        data[top] = c;
    }
    Cell pop()
    {
        Cell c = data[top];
        top--;
        return c;
    }
    Cell peek()
    {
        return data[top];
    }
    bool isEmpty()
    {
        return top == -1;
    }
};

std::vector<PunchedWall> build_maze(int n, int r, int c);
void print_maze(int n, const std::vector<PunchedWall> &v, int r, int c);
Cell find_cell(const Cell &x, int n, std::vector<std::vector<bool>> &visited);
int rand_dir(const Dir &d);
std::ostream& operator<<(std::ostream&  cout, const Stack &p);

#endif
