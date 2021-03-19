// #pragma once
#ifndef _HEX_BOARD
#define _HEX_BOARD
#include "Graph.h"
#include "HexPaths.h"
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

template<typename T>
class Graph<T>;

class HexPaths;

class HexBoard
{
private:
    int size;
    int numberOfNodes;
    Graph<int>  *board;
    std::vector<char> boardStatus;
    std::vector<int> top;
    std::vector<int> right;
    std::vector<int> bottom;
    std::vector<int> left;
    HexPaths *paths;
    bool blueHumanPlayer;
    bool redHumanPlayer;
    bool blueTurn;

    int isBoardEdge(int position);
    void printMove(int position, char value);
    int setPositionStatus(int position, char status);
    int makeMove(int position, char value);
    std::vector<int> valueConnections(int start, char value);
    bool isBlueVictory(int start);
    bool isRedVictory(int start);
    void moveAI();
    
public:
    HexBoard(int size);
    void printBoard();
    char getPositionStatus(int position);
    int coordinateToOrdinal(int x, int y);
    static int coordinateToOrdinal(int x, int y, int size);
    int ordinalToCoordinate(int position, int& x, int& y);
    static int ordinalToCoordinate(int position, int& x, int& y,int size);
    bool queryMove();
    inline void setBluePlayer(bool trueIfHuman){blueHumanPlayer = trueIfHuman;}
    inline void setRedPlayer(bool trueIfHuman){redHumanPlayer = trueIfHuman;}
};

#endif