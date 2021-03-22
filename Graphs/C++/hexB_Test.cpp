
#include "SimpleGraph.h"
#include "HexBoard.h"

int main(int argc, char const *argv[])
{
    const int size = 11;
    HexBoard board(size);
    bool gameEnded = false;
    

    while(!gameEnded){
        board.printBoard();
        gameEnded = board.queryMove();
    }

    return 0;
}