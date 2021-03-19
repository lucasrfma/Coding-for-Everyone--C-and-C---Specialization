/**
 * HexBoard class
 * 
 * Made for an assignment for C++ for C Programmers Part B - UCSC, @ Coursera
 * 
 * This is a class implements a game of Hex.
 * Currently it can create the board, ask for moves, put the moves on the board correctly, checking for errors
 *      such as trying to occupy and already occupied tile, or a tile out of bounds.
 * It also recognizes when a player has won the game.
 * 
 * There are 2 players: red and blue
 * Blue starts the match
 * Blue wins by connecting one side to the other
 * Red winds by connecting top and bottom
 * 
 * For testing purposes I'm sending this file together with the necessary Graph class and 2 test files
 *      How to use the test files:
 *      in windows 10: call the program with "cat test.txt | HexBoard.exe"
 *      Same should work on linux I think, probably just "HexBoard.exe << test.txt" works as well if I'm not mistaken
 * You can also test by playing a game with yourself I guess
 * You can change the size of the board by changing the size on main() function.
 * 
 * PS: the Graph class I'm using is the same I have created for C++ for C programmers Part A.
 * I think it is terrible for this case, since I made it by using connectivity matrices, which is a waste for this case
 * that has really low connectivity. But I guess it should'nt matter much, at least for now. Maybe for the future assignments,
 * which require more processing power for the AI part, I will change this.
 * 
 * Lucas Romero da Frota Moraes de Andrade.
 * mar. 11 2021
 * 
 */

#include "HexBoard.h"

using std::vector;
using std::string;

HexBoard::HexBoard(int size): size(size),paths(size), blueTurn(true), blueHumanPlayer(true), redHumanPlayer(true), numberOfNodes(size*size), board(size*size), boardStatus(size*size,'.')
{
    /**
     * Constructor that initializes a HexBoard.
     * int size argument is the size of a board edge.
     * So the total number of elements will be size squared.
     */
    // (test) std::cout << "\nSize is: " << size << std::endl;
    for( int i = 0; i < numberOfNodes; ++i){
        // Populate top vector.
        if( i < size ){
            top.push_back(i);
        }
        // Populate right vector
        if( (i % size) == (size - 1) ){
            right.push_back(i);
        }
        // Populate bottom vector
        if( i >= (size-1)*size ){
            bottom.push_back(i);
        }
        // Populate left vector
        if( (i % size) == 0 ){
            left.push_back(i);
        }
    }
    // (test) std::cout << "Vertices: " << board.Vertices() << std::endl;
    // (test) board.printGraph();

    // add the edges:
    int nodeType;
    for( int i = 0; i < numberOfNodes; ++i){
        nodeType = isBoardEdge(i);
        switch (nodeType)
        {
        case 0: // Inner position
            
            board.addEdge(i,i-size,1);
            board.addEdge(i,i-size+1,1);
            board.addEdge(i,i-1,1);
            board.addEdge(i,i+1,1);
            board.addEdge(i,i+size-1,1);
            board.addEdge(i,i+size,1);
            break;
        case 2: // Top Edge
            board.addEdge(i,i-1,1);
            board.addEdge(i,i+1,1);
            board.addEdge(i,i+size-1,1);
            board.addEdge(i,i+size,1);
            break;
        case 4: // Right Edge
            board.addEdge(i,i-size,1);
            board.addEdge(i,i-1,1);
            board.addEdge(i,i+size-1,1);
            board.addEdge(i,i+size,1);
            break;
        case 6: // Top-Right Corner
            board.addEdge(i,i-1,1);
            board.addEdge(i,i+size-1,1);
            board.addEdge(i,i+size,1);
            break;
        case 8: // Bottom Edge
            board.addEdge(i,i-size,1);
            board.addEdge(i,i-size+1,1);
            board.addEdge(i,i-1,1);
            board.addEdge(i,i+1,1);
            break;
        case 12: // Bottom-Right Cornerstd::cout << "test!!" << result;
            board.addEdge(i,i-size,1);
            board.addEdge(i,i-1,1);
            break;
        case 16: // Left Edge
            board.addEdge(i,i-size,1);
            board.addEdge(i,i-size+1,1);
            board.addEdge(i,i+1,1);
            board.addEdge(i,i+size,1);
            break;
        case 18: // Top-Left Corner
            // (test) std::cout << "Node " << i << " Type: " << nodeType;
            board.addEdge(i,i+1,1);
            board.addEdge(i,i+size,1);
            break;
        case 24: // Bottom-Left Corner
            board.addEdge(i,i-size,1);
            board.addEdge(i,i-size+1,1);
            board.addEdge(i,i+1,1);
            break;
        default:
            std::cout << "\nError checking element position." << std::endl;
            exit(1);
            break;
        }
    }
}

int HexBoard::isBoardEdge(int position)
{
/**
 *  2 ) int isBoardEdge(int position) - Returns an int representing what type of position it is:
 *      0 - Inner position;
 *      2 - Top edge position;
 *      4 - Right edge position;
 *      6 - Top-Right Corner position;
 *      8 - Bottom edge position;
 *      12 - Bottom-Right Corner position;
 *      16 - Left edge position;
 *      18 - Top-Left Corner position;
 *      24 - Bottom-Left Corner position;
 */
    int result = 0;

    for( int j = 0; j < size; ++j){
        if( top[j] == position ){
            result += 2;
        }
        if( right[j] == position ){
            result += 4;
        }
        if( bottom[j] == position ){
            result += 8;
        }
        if( left[j] == position ){
            result += 16;
        }
    }    
    // std::cout << "\nResult: " << result << std::endl;
    return result;
}

void HexBoard::printBoard()
{
    /**
     * Prints the current board.
     *  For example, a 5x5 board, with 3 plays by Blue and by Red:
     * 
     *     . - . - B - . - .
     *      \ / \ / \ / \ / \
     *       . - R - B - B - .
     *        \ / \ / \ / \ / \
     *         . - R - . - . - .
     *          \ / \ / \ / \ / \
     *           . - R - . - . - .
     *            \ / \ / \ / \ / \
     *             . - . - . - . - .
     */

    string space = "  ";
    string padding = "";
    std::cout <<  "\n";
    for( int i = 0; i < numberOfNodes; ++i){
        // If node i is the first of a line, print the padding to align the line
        // properly, then print the value of the node.
        if( i % size == 0 ){
            padding += space; 
            std::cout << padding << boardStatus[i];
        }else{
            // if it isn't the first of the line, print the link to the previous node
            // then the value of current node
            std::cout << " - " << boardStatus[i];
            // if node i is the last of a line, break line
            if( i % size == (size-1) ){
                std::cout << "\n";
                // if it's not the last line, add links to line below
                if( i != (numberOfNodes-1) ){
                    std::cout << padding;
                    for( int j = 0; j < (size-1); ++j){
                        std::cout << " \\ /";
                    }
                    std::cout << " \\" << "\n";
                }
            }
        } 
    }
    std::cout <<  "\n";
}

char HexBoard::getPositionStatus(int position)
{
    /**
     * Returns a char representing the status of the position
     * First checks if its a valid position. Returns '\0' if it isn't.
     */
    if( position < 0 || position >= numberOfNodes ){
        return '\0';
    }
    return boardStatus[position];
}

int HexBoard::setPositionStatus(int position, char value)
{
    /**
     * Sets a value to the position
     * First it checks if the position is valid - returns 1 for invalid position
     * Then checks if it is available to be claimed. - returns 2 for already claimed position
     * Checks if the value received is legal. Assigns it to boardStatus[position],
     * then returns 0 if all good.
     * returns 3 if bad value.
     */
    char current = getPositionStatus(position);
    if( current == '\0' ){
        return 1;
    }
    if( current != '.' ){
        return 2;
    }
    if( value == 'B' || value == 'R' ){
        boardStatus[position] = value;
        return 0;
    }
    return 3;
}

int HexBoard::coordinateToOrdinal(int x, int y)
{
    /**
     * Returns the ordinal value (from 0 to numberOfNodes-1) corresponding to
     * the coordinates passed. eg: (0,0) = 0, (n-1,n-1) = (n^2)-1
     * Returns -1 in case the resulting position is out of bounds.
     */
    int position = x*size + y;

    if( position < 0 || position >= numberOfNodes ){
        return -1;
    }
    return position;
}

int HexBoard::coordinateToOrdinal(int x, int y, int size)
{
    /**
     * Static version to enable other classes to use it even without direct access to a HexBoard Object.
     * Returns the ordinal value (from 0 to numberOfNodes-1) corresponding to
     * the coordinates passed. eg: (0,0) = 0, (n-1,n-1) = (n^2)-1
     * Returns -1 in case the resulting position is out of bounds.
     */
    int position = x*size + y;
    int numberOfNodes = size*size;

    if( position < 0 || position >= numberOfNodes ){
        return -1;
    }
    return position;
}

int HexBoard::ordinalToCoordinate(int position, int& x, int& y)
{
    /**
     * Converts a position to it's equivalent coordinates (x,y).
     * Checks if position is valid or out of bounds.
     * if out of bounds, returns -1 without assigning values.
     * If valid, (x,y) are assigned to the variables passes as arguments and returns 0
     */
    if( position < 0 || position >= numberOfNodes ){
        return -1;
    }
    x = position / size;
    y = position % size;
    return 0;
}

int HexBoard::ordinalToCoordinate(int position, int& x, int& y, int size)
{
    /**
     * Static version to enable other classes to use it even without direct access to a HexBoard Object.
     * Converts a position to it's equivalent coordinates (x,y).
     * Checks if position is valid or out of bounds.
     * if out of bounds, returns -1 without assigning values.
     * If valid, (x,y) are assigned to the variables passes as arguments and returns 0
     */
    int numberOfNodes = size*size;
    if( position < 0 || position >= numberOfNodes ){
        return -1;
    }
    x = position / size;
    y = position % size;
    return 0;
}

void HexBoard::printMove(int position, char value)
{
    /**
     * Prints a move. eg: "Blue claimed tile (x, y)"
     */
    int x,y;
    // no checking done since this is a private method.
    // leaves all checking to the calling methods.
    ordinalToCoordinate(position,x,y);
    if( value == 'B' ){
        std::cout << "\nBlue claimed tile (" << x << ", " << y << ")\n";
    } else if( value == 'R' ){
        std::cout << "\nRed claimed tile (" << x << ", " << y << ")\n";
    }
}

int HexBoard::makeMove(int position, char value)
{
    /**
     * Tries to make the move passed via arguments.
     * If all good, makes the move, prints it to screen and returns 0.
     * Otherwise, it will print an error message and return 1.
     */
    int check = setPositionStatus(position,value);
    if( check == 1 ){
        std::cout << "\nMove Failed. Intended position is out of bounds.\n";
        return 1;
    } else if( check == 2 ){
        std::cout << "\nMove Failed. Intended position is already occupied.\n";
        return 1;
    } else if( check == 3 ){
        std::cout << "\nMove Failed. Value must be either:\n'B' - Blue\n'R' - Red\n";
        return 1;
    } else{
        printMove(position, value);
        return 0;
    }
}

bool HexBoard::queryMove()
{
    /**
     * "Asks" for next move:
     *  1 - Verifies whose move it is
     *      - set the next move to be next players
     *  2 - Verifies if it's a human player or AI
     *      - Queries the user for coordinate input
     *      - Calls decision making method
     *  3 - makes move with resulting values
     *  4 - verifies if game has been won. Returns True if it has.
     */

    int x,y,position,fail;
    char value;
    bool victory = false;
    if( blueTurn ){
        value = 'B';
        if( blueHumanPlayer ){
            std::cout << "\nBlue Player Turn. Enter desired tile's coordinates:\nVertical from 0 to " << size-1 <<": ";
            std::cin >> x;
            std::cout << "\nHorizontal from 0 to " << size-1 <<": ";
            std::cin >> y;
            position = coordinateToOrdinal(x,y);
        }else{
            moveAI();
        }
        if( !( fail = makeMove(position,'B') ) ){
            // changes whose turn it is
            blueTurn = false;
            // check if the position is in either edges necessary to win. If it is, runs a victory check
            if ( (std::find(left.begin(),left.end(),position) != left.end()) || (std::find(right.begin(),right.end(),position) != right.end()) ){
                if( victory = isBlueVictory(position) ){
                    std:: cout << "\nTesting pos: " << position <<"\n";
                    printBoard();
                    std::cout << "\nBlue Player is victorious!!\n\n";
                }
            }
        }

    } else{
        value = 'R';
        if( redHumanPlayer ){
            std::cout << "\nRed Player Turn. Enter desired tile's coordinates:\nVertical from 0 to " << size-1 << ": ";
            std::cin >> x;
            std::cout << "\nHorizontal from 0 to " << size-1 << ": ";
            std::cin >> y;
            position = coordinateToOrdinal(x,y);
        } else{
            moveAI();
        }
        if( !( fail = makeMove(position,'R') ) ){
            // changes whose turn it is
            blueTurn = true;
            // check if the position is in either edges necessary to win. If it is, runs a victory check
            if ( (std::find(top.begin(),top.end(),position) != top.end()) || (std::find(bottom.begin(),bottom.end(),position) != bottom.end()) ){
                if( victory = isRedVictory(position) ){
                    printBoard();
                    std::cout << "\nRed Player is victorious!!\n\n";
                }
            }
        }
    }
    return victory;
}

vector<int> HexBoard::valueConnections(int start, char value)
{
    /**
     * returns a vector with all nodes that create a path from start node.
     * each node in the path must have the specified value. Used to determine win condition.
     */
    vector<int> connections;
    vector<int> toVisit;
    vector<int> visited;
    vector<int> neighbors;
    int current;

    // adds start to toVisit
    toVisit.push_back(start);

    while( !toVisit.empty() ){

        // assign the last value in toVisit to current
        current = toVisit.back();
        // remove that value from toVisit
        toVisit.pop_back();

        // no need to revisit nodes, so just visit ones not found on the visit vector
        auto check = std::find(visited.begin(),visited.end(),current);
        if( check == visited.end() ){
            // mark current as visited
            visited.push_back(current);
            // if current's board status is equal to value, it is part of the path
            if( boardStatus[current] == value ){
                // add to path
                connections.push_back(current);
                // add it's neighbors to toSee
                neighbors = board.Neighbors(current);
                toVisit.insert(toVisit.end(),neighbors.begin(),neighbors.end());
            }
        }
    }

    return connections;
}

bool HexBoard::isBlueVictory(int start)
{
    /** 
     * Test if there is a Blue path spanning from left to right edge,
     * using the argument start as the starting point.
     * It doesn't need to go checking every edge node as a possible start,
     * since it's a private method that will be automatically called in case 
     * an left or right edge tile is claimed by Blue
     */
    vector<int> path = valueConnections(start,'B');
    bool foundLeft = false, foundRight = false;
    for (auto tile : path)
    {
        if( !foundLeft ){
            // auto location = std::find(left.begin(),left.end(),"B");
            if( std::find(left.begin(),left.end(),tile) != left.end() ){
                foundLeft = true;
            }
        }
        if( !foundRight ){
            // auto location = std::find(right.begin(),right.end(),"B");
            if( std::find(right.begin(),right.end(),tile) != right.end() ){
                foundRight = true;
            }
        }
    }
    return foundLeft&&foundRight;
}

bool HexBoard::isRedVictory(int start)
{
    /** 
     * Test if there is a Red path spanning from top to bottom edge,
     * using the argument start as the starting point.
     * It doesn't need to go checking every edge node as a possible start,
     * since it's a private method that will be automatically called in case 
     * an Top or bottom edge tile is claimed by Red
     */
    vector<int> path = valueConnections(start,'R');
    bool foundTop = false, foundBottom = false;
    
    for (auto tile : path)
    {
        if( !foundTop ){
            auto location = std::find(top.begin(),top.end(),tile);
            if( location != top.end() ){
                foundTop = true;
            }
        }
        if( !foundBottom ){
            auto location = std::find(bottom.begin(),bottom.end(),tile);
            if( location != bottom.end() ){
                foundBottom = true;
            }
        }
    }
    return foundTop&&foundBottom;
}

void HexBoard::moveAI()
{

}
