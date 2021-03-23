/**
 * Coursera - C++ for C Programmers, Part B
 * Implement Monte Carlo Hex Move
 * 
 * This program is set to run 50,000 simulations per play if the board is small (7 or less)
 * and 25.000 if it is large (8 or more)
 * 
 * The assignment tells us to not make it take longer than 2 minutes, but since the computers can vary a lot
 * I decided to make it do few tests. (And the assignment asks for only 1000 per play anyway...)
 * 
 * There are 2 players: red and blue
 * Blue starts the match
 * Blue wins by connecting one side to the other
 * Red winds by connecting top and bottom
 * 
 * Lucas Romero da F. M. de Andrade
 * march 23 2021
 * 
 */


#include "SimpleGraph.h"
#include "HexBoard.h"
#include <iostream>

using std::cout;
using std::cin;
using std::endl;

int main(int argc, char const *argv[])
{
    
    int simulationNumber = 50000;
    int size,option;
    cout << "\nPlease enter board size (ex: 7)\n";
    cin >> size;
    // to avoid long wait times
    if(size > 7)
    {
        simulationNumber = 25000;
    }
    HexBoard board(size,simulationNumber);

    cout << "\nChoose an Option: \n1 - Player (Blue) VS AI (Red)\n2 - AI (Blue) VS Player (Red)\n3 - AI VS AI\n4 - Player VS Player\n";
    cin >> option;

    switch (option)
    {
    case 2:
        board.setBluePlayer(false); break;
    case 3:
        board.setBluePlayer(false);
        board.setRedPlayer(false); break;
    case 4:
        break;
    default:
        board.setRedPlayer(false);
        break;
    }
    
    bool gameEnded = false;
    while(!gameEnded){
        board.printBoard();
        gameEnded = board.queryMove();
    }

    return 0;
}