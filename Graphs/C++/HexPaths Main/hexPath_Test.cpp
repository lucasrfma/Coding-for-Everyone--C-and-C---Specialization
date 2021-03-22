#include "..\\HexPaths.h"
#include <iostream>

using std::cout;
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
