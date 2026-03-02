//===========================================================
//
//  File : main.cpp
//  Author : Brysen Landis
//
//  Description : Random Maze Generator for take home Mid Term
//
//===========================================================

#include <iostream>
#include <vector>
#include <ctime>
#include "Maze.h"

int main()
{
    srand((unsigned int) time(NULL));
    int n, r, c;
    std::cin >> n >> r >> c;
    std::vector<PunchedWall> punched_walls = build_maze(n, r, c);
    print_maze(n, punched_walls, r, c);

    return 0;
}
