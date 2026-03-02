#include <iostream>
#include <ctime>
#include <vector>
#include "Maze.h"


int rand_dir(const Dir &d)
{
    if (d.top == 0)
    {
        return -1;
    }
    
    int idx = rand() % d.top;
    int dir = d.dirs[idx];
    return dir;
}


Cell find_cell(const Cell &x, int n,
               std::vector<std::vector<bool>> &visited)
{
    Dir d; d.top = 0;
    // north check
    if (x.r - 1 >= 0 && !visited[x.r - 1][x.c])
    {
        d.dirs[d.top] = 0;
        ++d.top;
    }
    // south check
    if (x.r + 1 <= n - 1 && !visited[x.r + 1][x.c])
    {
        d.dirs[d.top] = 1;
        ++d.top;
    }
    // east check
    if (x.c + 1 <= n - 1 && !visited[x.r][x.c + 1])
    {
        d.dirs[d.top] = 2;
        ++d.top;
    }
    // west check
    if (x.c - 1 >= 0 && !visited[x.r][x.c - 1])
    {
        d.dirs[d.top] = 3;
        ++d.top;
    }
    // select a random direction based off of available cells surrounding point
    int r_dir = rand_dir(d);
    
    // if r_dir returns no valid direction return the sentinal cell
    // when there are no other cells left to move to.
    if (r_dir == -1)
    {
        Cell none; none.r = -1; none.c = -1;
        return none;
    }

    Cell next;
    // compute the north cell
    if (r_dir == 0)
    {
        // set the cell north of x to true as visited
        visited[x.r - 1][x.c] = true;
        next.r = x.r - 1;
        next.c = x.c;
    }
    // compute the south cell
    if (r_dir == 1)
    {
        // set the cell south of x to true as visited
        visited[x.r + 1][x.c] = true;
        next.r = x.r + 1;
        next.c = x.c;
    }
    // compute the east cell
    if (r_dir == 2)
    {
        // set the cell east of x to true as visited
        visited[x.r][x.c + 1] = true;
        next.r = x.r;
        next.c = x.c + 1;
    }
    // compute the west cell
    if (r_dir == 3)
    {
        // set the cell west of x to true as visited
        visited[x.r][x.c - 1] = true;
        next.r = x.r;
        next.c = x.c - 1;
    }
    return next;
}


void print_maze(int n, const std::vector<PunchedWall> &v, int r, int c)
{
    // lambda to check if wall between two cells is punched
    auto is_punched = [&](Cell a, Cell b)
    {
        for (const PunchedWall &pw : v)
        {
            if ((pw.c0.r == a.r && pw.c0.c == a.c &&
                 pw.c1.r == b.r && pw.c1.c == b.c) ||
                (pw.c1.r == a.r && pw.c1.c == a.c &&
                 pw.c0.r == b.r && pw.c0.c == b.c))
                return true;
        }
        return false;
    };

    for (int i = 0; i < n; ++i)
    {
        // print top wall of each row
        for (int j = 0; j < n; ++j)
        {
            Cell above; above.r = i - 1; above.c = j;
            Cell curr;  curr.r  = i;     curr.c  = j;
            std::cout << "+";
            std::cout << (i == 0 || !is_punched(curr, above) ? "-" : " ");
        }
        std::cout << "+\n";

        // print left wall and cell interior
        for (int j = 0; j < n; ++j)
        {
            Cell left; left.r = i; left.c = j - 1;
            Cell curr; curr.r  = i; curr.c  = j;
            std::cout << (j == 0 || !is_punched(curr, left) ? "|" : " ");
            std::cout << (i == r && j == c ? "X" : " ");  // mark start
        }
        std::cout << "|\n";
    }

    // print bottom wall
    for (int j = 0; j < n; ++j)
        std::cout << "+-";
    std::cout << "+\n";
}


std::vector<PunchedWall> build_maze(int n, int r, int c)
{
    // create vector of size n^2 and set all cells to false
    std::vector<std::vector<bool>> visited(n, std::vector<bool>(n, false));
    std::vector<PunchedWall> walls;
    visited[r][c] = true; // set starting point to true
    Stack path; // create stack
    Cell start; // create starting cell on stack
    start.r = r; // init row
    start.c = c; // init col
    path.push(start); // push cell to stack
    
    Cell x; // create new cell
    while(!path.isEmpty())
    {
        x = path.peek();
        Cell next = find_cell(x, n, visited);
        if (next.r == -1)  // dead end signal
        {
            path.pop();
        }
        else if (next.r != x.r || next.c != x.c)
        {
            PunchedWall pw; // record the punched wall
            pw.c0 = x;
            pw.c1 = next;
            walls.push_back(pw);
            path.push(next);
        }
    }
    
    return walls;
}
