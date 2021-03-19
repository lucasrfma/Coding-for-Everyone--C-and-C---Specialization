#ifndef _HEX_PATHS
#define _HEX_PATHS
/**
 * This is a simple class that will manage paths created on a HexBoard
 * It will keep track of existing paths.
 * It will merge paths when needed
 * The paths will be provided by the board itself
 */
// #include <iostream>
#include <list>
#include <vector>

class HexPaths
{
private:
    int size;
    std::list<std::vector<int>> paths;
public:
    HexPaths();
    HexPaths(int size):size(size){}
};

#endif