/**
 * Hex plausible move selector
 * This class will have methods dedicated to detecting plausible moves
 *  
 * Plausible move definitions:
 * 1 - A winning move
 * 2 - A winning move prevention move
 * 3 - Path extension move
 * 4 - Path extension blocking move
 * 5 - Path Bridging move
 * 6 - New Territory move
 * 
 * Should define:
 *  - A maximum amount of moves to consider
 * Principles to follow:
 * Should try to make moves on the center of the board.
 * Should try to retain information used on previous moves to quicken new decisions
 *      - for this an array of Paths might be usefull, since paths are not unmade.
 * 
*/

#include <iostream>
#include <vector>
#include "HexBoard.cpp"

class HexMoveSelector
{
private:
    HexBoard board;
    vector<vector<int>> bluePaths;
    vector<vector<int>> redPaths;

public:
    int checkForWinningMove();

};

int HexMoveSelector::checkForWinningMove()
{
    
}