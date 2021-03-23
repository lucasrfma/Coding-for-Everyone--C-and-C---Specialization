// #pragma once
#pragma once

#include "SimpleGraph.h"
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <chrono>
#include <random>

class HexPaths;

class HexBoard
{
private:

    int size;
    int numberOfNodes;
    int simulationNumber;
    int threadNumber;
    SimpleGraph  board;
    std::vector<char> boardStatus;
    std::vector<int> top;
    std::vector<int> right;
    std::vector<int> bottom;
    std::vector<int> left;
    bool blueHumanPlayer;
    bool redHumanPlayer;
    bool blueTurn;
    std::default_random_engine randomizer;

    int isBoardEdge(int position);
    void printMove(int position, char value);
    int setPositionStatus(int position, char status);
    int makeMove(int position, char value);
    std::vector<int> valueConnections(int start, char value);
    bool isBlueVictory(int start);
    bool isRedVictory(int start);
    std::vector<int> valueConnectionsSim(int start, const std::vector<char> &simulation);
    bool isBlueVictorySim(int start, const std::vector<char> &simulation);
    int moveAI();
    std::vector<double> monteCarlo();
    

public:
    HexBoard(int size,int sim, int threadNumber);
    void printBoard();
    char getPositionStatus(int position);
    int coordinateToOrdinal(int x, int y);
    int ordinalToCoordinate(int position, int& x, int& y);
    bool queryMove();
    inline void setBluePlayer(bool trueIfHuman){blueHumanPlayer = trueIfHuman;}
    inline void setRedPlayer(bool trueIfHuman){redHumanPlayer = trueIfHuman;}
};