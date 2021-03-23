/**
 * Coursera - C++ for C Programmers, Part B
 * Implement Monte Carlo Hex Move
 * 
 * This program is set to run 110,000 simulations per move.
 * This is because the assignment asks for +- 1000 trials per legal play
 * and the first moves in a 11x11 board will have more than 110 legal play
 * but the number of legal play drops every move.
 * I though of setting a specific number of trials per possible play, instead of per move
 * but then I decided it wouldn't make much difference, so here we are.
 * This way is nice that we can choose the simulation number based on what is a tolerable wait time
 * and the "precision" of the AI goes up as the game goes on. It still gets faster since each trial
 * gets smaller as the possible moves get fewer.
 * 
 * There are 2 players: red and blue
 * Blue starts the match
 * Blue wins by connecting one side to the other
 * Red winds by connecting top and bottom
 * 
 * I originally created this with separated files, as I had done in other assignments
 * But since everyone always uploads their assignments as a single file, maybe that's the correct way to do it
 * so copy pasted everything into one .cpp. Hope you dont mind!
 * 
 * Lucas Romero da F. M. de Andrade
 * march 23 2021
 * 
 */

#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <algorithm>
#include <chrono>
#include <random>

using std::cout;
using std::cin;
using std::endl;
using std::vector;
using std::string;

/**
 * SimpleGraph declaration
 * Implementation is pasted beneath the main function.
 */

class SimpleGraph{
private:

    int size;
    int edges;
    std::vector<std::vector<int>> graph;

public:

    SimpleGraph(int size): size(size),edges(0),graph(size){}
    // returns true if nodes are adjacent
    bool Adjacent(int node1, int node2);
    /**
     * Adds an edge
     * only does anything if the edge really did not exist.
     */
    void addEdge(int node1, int node2);
    // returns the number of edges
    int Edges();
    // returns a list of adjacent nodes
    std::vector<int> Neighbors(int node);
    /**
     * prints a table of connectivity representing the graph
     */
    void printGraph();
};

/**
 * HexBoard declaration
 * Implementation is pasted beneath the main function.
 */
class HexBoard
{
private:

    int size;
    int numberOfNodes;
    int simulationNumber;
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
    HexBoard(int size,int sim);
    void printBoard();
    char getPositionStatus(int position);
    int coordinateToOrdinal(int x, int y);
    int ordinalToCoordinate(int position, int& x, int& y);
    bool queryMove();
    inline void setBluePlayer(bool trueIfHuman){blueHumanPlayer = trueIfHuman;}
    inline void setRedPlayer(bool trueIfHuman){redHumanPlayer = trueIfHuman;}
};

/**
 * Main Function
 */

int main(int argc, char const *argv[])
{
    // default number of simulations per AI play
    int simulationNumber = 110000;
    int size,option;
    cout << "\nPlease enter board size (ex: 7)\n";
    cin >> size;
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
    // plays the game until it ends
    while(!gameEnded){
        board.printBoard();
        gameEnded = board.queryMove();
    }

    return 0;
}

/**
 * SimpleGraph Implementation
 */
bool SimpleGraph::Adjacent(int node1, int node2){
    // returns true if there is an edge between the nodes
    return ( std::find(graph[node1].begin(),graph[node1].end(),node2) != graph[node1].end() );
}

void SimpleGraph::addEdge(int node1, int node2){
    /**
     * adds an edge with the specified weight/distance between the specified nodes
     * only does anything if the edge really did not exist.
     */
    if( !Adjacent(node1,node2) ){
        // (test) std::cout << "\nNew edge between node " << node1 << " and node 2 " << node2 << " Distance: " << distance << std::endl; 
        graph[node1].push_back(node2);
        graph[node2].push_back(node1);
        ++edges;
    }
}

int SimpleGraph::Edges(){
    // returns the number of edges
    return edges;
}

vector<int> SimpleGraph::Neighbors(int node){
    /**
     * returns a vector of ints indicating which nodes have edges with the specified node.
     */
    return graph[node];
}

void SimpleGraph::printGraph(){
    /**
     * Prints the graph
     */
    
    cout << "\nNode | Connections" << endl;
    int i = 0;
    for (auto &&node : graph)
    {
        cout << "\n" << std::setw(4) << i << " | ";
        for (auto &&edge : node)
        {
            cout << edge << " ";
        }
        ++i;
    }   
}

/**
 * HexBoard Implementation
 */
HexBoard::HexBoard(int size,int sim): simulationNumber(sim), size(size), blueTurn(true), blueHumanPlayer(true), redHumanPlayer(true), numberOfNodes(size*size), board(size*size), boardStatus(size*size,'.')
{
    /**
     * Constructor that initializes a HexBoard.
     * int size argument is the size of a board edge.
     * So the total number of elements will be size squared.
     */

    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    randomizer.seed(seed);

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

    // add the edges:
    int nodeType;
    for( int i = 0; i < numberOfNodes; ++i){
        nodeType = isBoardEdge(i);
        switch (nodeType)
        {
        case 0: // Inner position
            
            board.addEdge(i,i-size);
            board.addEdge(i,i-size+1);
            board.addEdge(i,i-1);
            board.addEdge(i,i+1);
            board.addEdge(i,i+size-1);
            board.addEdge(i,i+size);
            break;
        case 2: // Top Edge
            board.addEdge(i,i-1);
            board.addEdge(i,i+1);
            board.addEdge(i,i+size-1);
            board.addEdge(i,i+size);
            break;
        case 4: // Right Edge
            board.addEdge(i,i-size);
            board.addEdge(i,i-1);
            board.addEdge(i,i+size-1);
            board.addEdge(i,i+size);
            break;
        case 6: // Top-Right Corner
            board.addEdge(i,i-1);
            board.addEdge(i,i+size-1);
            board.addEdge(i,i+size);
            break;
        case 8: // Bottom Edge
            board.addEdge(i,i-size);
            board.addEdge(i,i-size+1);
            board.addEdge(i,i-1);
            board.addEdge(i,i+1);
            break;
        case 12: // Bottom-Right Corner
            board.addEdge(i,i-size);
            board.addEdge(i,i-1);
            break;
        case 16: // Left Edge
            board.addEdge(i,i-size);
            board.addEdge(i,i-size+1);
            board.addEdge(i,i+1);
            board.addEdge(i,i+size);
            break;
        case 18: // Top-Left Corner
            board.addEdge(i,i+1);
            board.addEdge(i,i+size);
            break;
        case 24: // Bottom-Left Corner
            board.addEdge(i,i-size);
            board.addEdge(i,i-size+1);
            board.addEdge(i,i+1);
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
            position = moveAI();
        }
        if( !( fail = makeMove(position,'B') ) ){
            // changes whose turn it is
            blueTurn = false;
            if( victory = isBlueVictory(position) ){
                std:: cout << "\nTesting pos: " << position <<"\n";
                printBoard();
                std::cout << "\nBlue Player is victorious!!\n\n";
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
            position = moveAI();
        }
        if( !( fail = makeMove(position,'R') ) ){
            // changes whose turn it is
            blueTurn = true;
            if( victory = isRedVictory(position) ){
                printBoard();
                std::cout << "\nRed Player is victorious!!\n\n";
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

vector<int> HexBoard::valueConnectionsSim(int start, const vector<char> &simulation)
{
    /**
     * Version to be used on simulations. Basically the same as the regular one, but
     * compares to a vector<char> received by argument, instead of the regular one of the board.
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
            // if current's board status is equal to Blue, it is part of the path
            if( simulation[current] == 'B' ){
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

bool HexBoard::isBlueVictorySim(int start, const vector<char> &simulation)
{
    /** 
     * Version to be used on simulations. Basically the same as the regular one, but
     * compares to a vector<char> received by argument, instead of the regular one of the board.
     * As the monteCarlo method always runs the check starting from the left tiles, it is uneeded to
     * check left tiles in this version
     * 
     * Test if there is a Blue path spanning from left to right edge,
     * using the argument start as the starting point.
     * It doesn't need to go checking every edge node as a possible start,
     * since it's a private method that will be automatically called in case 
     * an left or right edge tile is claimed by Blue
     */
    vector<int> path = valueConnectionsSim(start,simulation);
    bool foundRight = false;
    for (auto tile : path)
    {
        if( std::find(right.begin(),right.end(),tile) != right.end() ){
            foundRight = true;
            break;
        }
    }
    return foundRight;
}

int HexBoard::moveAI()
{
    /**
     * Calls monteCarlo()
     * Chooses the appropriate tile to take based on the vector returned
     * Returns the position of the tile
     */
    cout << "\nProcessing ... \n";
    vector<double> &&blueWinRate = monteCarlo();
    int position = numberOfNodes;
    double comparison;
    // if blue turn, finds the biggest winRate and returns the respective starting move
    if(blueTurn)
    {
        comparison = -1.0;
        int i = 0;
        for (auto winrate : blueWinRate)
        {
            if( winrate > comparison )
            {
                position = i;
                comparison = winrate;
            }
            ++i;
        }
        
    }
    else // if not, finds the lowest win rate.
    {
        comparison = 2.0;
        int i = 0;
        for (auto winrate : blueWinRate)
        {
            // -1.0 is the default when creating the blueWinRate vector
            // It is not 0 so a position not considered is different from a position with blue = 0% wr
            if( winrate < comparison && winrate != -1.0)
            {
                position = i;
                comparison = winrate;
            }
            ++i;
        }
    }
    return position;
}

vector<double> HexBoard::monteCarlo()
{
    /**
     * 1 - Creates a copy of boardStatus, and blueTurn
     * 2 - Creates a vector to represent blue win %, once to represent wins, and one totals for every starting tile
     * 3 - Creates a vector with all unclaimed tiles
     * 4 - Simulates plays, sees if Blue won in each simulated game
     * 5 - calculates win rate for each starting move and returns it
     */

    // 1 - Creates a copy of boardStatus, and blueTurn
    vector<char> simulation = boardStatus;
    bool blueTurnSim = blueTurn;

    // for (auto tile : boardStatus)
    // {
    //     cout<<tile;
    // }    

    // 2 - Creates a vector to represent blue win %, once to represent wins, and one totals for every starting tile
    vector<double> blueWinRate(numberOfNodes,-1.0);
    vector<int> blueWins(numberOfNodes,0);
    vector<int> totals(numberOfNodes,0);
    // 3 - Creates a vector with all unclaimed tiles
    vector<int> unclaimed;
    int i = 0;
    for (auto tile : simulation)
    {
        if(tile == '.')
        {
            unclaimed.push_back(i);
        }
        ++i;
    }

    // 4 - Simulates plays, sees if Blue won in each simulated game
    for( int j = 0; j < simulationNumber; ++j )
    {
        // Shuffles unclaimed vector to simulate a game
        std::shuffle(unclaimed.begin(),unclaimed.end(),randomizer);
        // increment number of games starting with the first position of the unclaimed vector
        // each position on this vector represents a play
        ++totals[unclaimed[0]];
        // goes trough the unclaimed vector making the plays until the simulation board is filled
        for (auto position : unclaimed)
        {
            if(blueTurnSim)
                simulation[position] = 'B';
            else
                simulation[position] = 'R';
            blueTurnSim = !blueTurnSim;
        }
        // verifies if blue won
        for (auto tile : left)
        {
            if( isBlueVictorySim(tile,simulation) )
            {
                ++blueWins[unclaimed[0]];
                break;
            }
        }
    }

    // 5 calculates win rate for each starting move and returns it
    int k = 0;
    for (auto games : totals)
    {
        if( games > 0 )
        {
            blueWinRate[k] = static_cast<double>(blueWins[k])/games;
        }
        ++k;
    }
    return blueWinRate;
}