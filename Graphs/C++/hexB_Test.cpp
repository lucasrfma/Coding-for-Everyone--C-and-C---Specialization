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
    
    int simulationNumber = 10000;
    int size,option,threads;
    cout << "\nHex Game\n" <<"\nPlease enter board size (I recomend from 7 to 11)\n";
    cin >> size;
    simulationNumber *= size;
    cout << "\nPlease enter how many CPU cores to use.\n";
    cin >> threads;
    HexBoard board(size,simulationNumber,threads);

    cout << "\nBlue player needs to connect Left and Right sides of the board.\nRed player needs to connect Top and Bottom";
    cout << "\nChoose an Option: \n1 - Player (Blue) VS AI (Red)\n2 - AI (Blue) VS Player (Red)\n3 - AI VS AI\n4 - Player VS Player\n\n";
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