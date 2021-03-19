#pragma once

/**
 * This is a simple class that will manage paths created on a HexBoard
 * It will keep track of existing paths.
 * It will merge paths when needed
 * The paths will be provided by the board itself
 */

#include "HexBoard.h"
// #include <iostream>
#include <list>
#include <vector>

class HexPaths
{
private:
    int size;
    // int numberOfNodes;
    std::list<std::vector<int>> paths;
public:
    HexPaths(){}
    HexPaths(int size):size(size){}
    void setSize(int size){size = size;}

};