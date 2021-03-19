/**
 * This is a simple class that will manage paths created on a HexBoard
 * It will keep track of existing paths.
 * It will merge paths when needed
 * The paths will be provided by the board itself
 */


#include "HexPaths.h"
// #include "HexBoard.h"
// // #include <iostream>
// #include <list>
// #include <vector>


// class HexPaths
// {
// private:
//     int size;
//     // int numberOfNodes;
//     list<vector<int>> paths;
// public:
//     HexPaths(){}
//     HexPaths(int size):size(size){}
//     void setSize(int size){size = size;}

// };

using std::vector;
using std::list;
using std::cout;
using std::cin;
using std::endl;


int main(int argc, char const *argv[])
{
    int position = 15, x, y, boardSize = 11;
    HexBoard::ordinalToCoordinate(position,x,y,boardSize);
    cout << "Position " << position << "'s coordinates are:\nx: "<< x << "\ny: "<< y <<  endl;
    cout << "Coordinates x =  " << x << ", y = " << y << "'s ordinal position is: " << HexBoard::coordinateToOrdinal(x,y,boardSize) << endl;
    x = 3;
    y = 9;
    cout << "Coordinates x =  " << x << ", y = " << y << "'s ordinal position is: " << HexBoard::coordinateToOrdinal(x,y,boardSize) << endl;
    return 0;
}




