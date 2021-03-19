/*     
    
    mar. 6 2021:
        Changed to be a template. It should work properly with either integer or floating point types.
        It changes the graph attribute from a vector<vector<int>> to a template<typename T> vector<vector<T>
    This type basically determines the type of the edge weights. So by doing this, the class is able to represent different kinds of weights, from
    unweighted to a high precision floating point (double).

    *I have changed my mind about this paragraph below and intend to change it in the future:
    For the graph representation as a data structure I decided to use a square matrix created by a 2d vector. 
    Although making it a square matrix means it will take up more memory than a vector of differently sized vectors, 
    it also is, in my opinion, easier to think about and understand,
    so it should result in simpler and faster algorithms.
    
    Originally made for the week 3 Assignment for the course "C++ for C Programmers, Part A", University of California - Santa Cruz @ Coursera
    Changes have been made to increase ways it can be used, and help in following assignments.

  Lucas Romero da F M de Andrade
  Start: feb. 17 2021
  End: feb. 20 2021
*/

// #include <cstdlib>
#include <iostream>
#include <iomanip>
#include <vector>
#include <chrono>
#include <random>
#include <fstream>
#include <iterator>
#include <type_traits>

using std::vector;
using std::cout;
using std::default_random_engine;

template <typename T>
class Graph{

public:

    Graph(int size = 10):size(size), edges(0), graph(size,vector<T>(size,static_cast<T>(0))){
        /**
         * Constructor that creates a completely unconnected graph of size size.
         * Also seeds the pseudo-random number generator to be used with randomizeGraph().
         */
        seedRandomNumberGen();
    }

    Graph(const vector<vector<T>>& newGraph){
        /**
         * Constructor that makes the graph from an existing 2d vector.
         */
        graph = newGraph;
        size = graph.size();
        edges = 0;
        for( int i = 0; i < graph.size(); ++i ){
            for( int j = 0; j < graph[i].size(); ++j){
                if( graph[i][j] != static_cast<T>(0) ){
                    ++edges;
                }
            }
        }
    }

    Graph(std::string file_name): edges(0){
        /**
         * Constructor that makes the graph from file.
         * The file format will be an initial integer that is the node size of the graph
         * and the further values will be: (i, j, cost). 
         * where i and j are integers that define the nodes, and cost is the edge weight
         */
        std::ifstream input_file(file_name);
        std::istream_iterator<int> start(input_file), end; // create iterators

        std::vector<double> fileData(start,end);        // use iterators to create an vector with all the file data
                                                        // this vector is of double, since it's the most capable native type
                                                        // So it should be able to read ints and be converted to ints properly
                                                        // for the "size" and "node" information.
                                                        // as well as retain the information necessary for the weight information
                                                        // regardless of the used type (if its a native type or convertible from double)

        size = static_cast<int>(fileData[0]);           // read the graph size
        graph.resize(size,vector<T>(size,static_cast<T>(0)));           // initialize the graph with the size read, all nodes unconnected

        // this loop will go through the values read, starting from the second (since the first was the node size)
        // each iteration increases by 3, since each edge is a triple.
        for( int i = 1; i < fileData.size(); i += 3){
                                        //i                                 j                               cost
            addEdge( static_cast<int>(fileData[i]) , static_cast<int>(fileData[i+1]), static_cast<T>(fileData[i+2]));
        }
    }

    void seedRandomNumberGen(){
        /**
         * Method for seeding the pseudo random number generator used in randomizeGraph()
         */
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        generator.seed(seed);
    }

    int Vertices(){
        // returns the number of vertices
        return size;
    }

    int Edges(){
        // returns the number of edges
        return edges;
    }

    bool Adjacent(int node1, int node2){
        // returns true if there is an edge between the nodes
        return ( graph[node1][node2] != static_cast<T>(0) );
    }

    vector<int> Neighbors(int node){
        /**
         * returns a vector of ints indicating which nodes have edges with the specified node.
         */
        vector<int> neighbors;

        for( int i = 0; i < size; ++i){
            if( graph[node][i] != static_cast<T>(0)){
                neighbors.push_back(i);
            }
        }

        return neighbors;
    }

    void addEdge(int node1, int node2, T distance){
        /**
         * adds an edge with the specified weight/distance between the specified nodes
         * only does anything if the edge really did not exist.
         */
        if( !Adjacent(node1,node2) ){
            // (test) std::cout << "\nNew edge between node " << node1 << " and node 2 " << node2 << " Distance: " << distance << std::endl; 
            graph[node1][node2] = graph[node2][node1] = distance;
            ++edges;
        }
    }

    void deleteEdge(int node1, int node2){
        /**
         * removes the edge between the specified nodes
         * only does anything if the edge really exists.
         */
        if( Adjacent(node1,node2)){
            graph[node1][node2] = graph[node2][node1] = static_cast<T>(0);
            --edges;
        }
    }

    T getEdgeValue(int node1, int node2){
        /**
         * returns the weight of the edge between specified nodes
         */
        return graph[node1][node2];
    }

    void setEdgeValue(int node1, int node2, T value){
        /**
         * changes the weight/distance of an existing edge
         * to avoid misuse, this method checks if deleteEdge or addEdge aren't
         * the proper methods before actually changing the value.
         */
        if( !Adjacent(node1,node2) ){
            addEdge(node1,node2,value);
        }else if( value == static_cast<T>(0)){
            deleteEdge(node1,node2);
        }else{
            graph[node1][node2] = graph[node2][node1] = value;
        }
    }

    void randomizeGraph( const double density = 0.2, const T minDistance = static_cast<T>(1.0), const T maxDistance = static_cast<T>(10.0)){
        /**
         * This function creates randomized edges on the graph.
         * The user can specify density, as well as the minimum and maximum edge weight/distance
         * If no arguments are specified, the density will be of 20%, minimum distance of 1.0 and maximum of 10.0
         */

        // to decide if there is or there is not an edge between 2 nodes
        std::uniform_real_distribution<double> rollEdgePresence(0.0,1.0);
        // to decide the size of an edge.
        std::uniform_int_distribution<long long> rollDistanceIntegral(minDistance,maxDistance);
        std::uniform_real_distribution<double> rollDistanceDouble(minDistance,maxDistance);
        
        if( std::is_integral<T>::value ){
            for(int i = 0; i < size; ++i){
                for(int j = 0; j < size; ++j){
                    // no loop edges, so we do nothing when i == j
                    // since the edges are bidirectional, graph[i][j] should be equal to graph[j][i]. addEdge() already sets both ways.
                    // so we only do anything when j > i.
                    if ( j > i){
                        if( rollEdgePresence(generator) < density ){
                            T edgeValue = static_cast<T>(rollDistanceIntegral(generator));
                            addEdge(i,j,edgeValue);
                        }
                    }
                }
            }
        } else if( std::is_floating_point<T>::value ){
            for(int i = 0; i < size; ++i){
                for(int j = 0; j < size; ++j){
                    // no loop edges, so we do nothing when i == j
                    // since the edges are bidirectional, graph[i][j] should be equal to graph[j][i]. addEdge() already sets both ways.
                    // so we only do anything when j > i.
                    if ( j > i){
                        if( rollEdgePresence(generator) < density ){
                            T edgeValue = static_cast<T>(rollDistanceDouble(generator));
                            addEdge(i,j,edgeValue);
                        }
                    }
                }
            }
        }
    }

    void printGraph(){
        /**
         * prints a table representing the graph
         */
        
        cout << "\n    ";
        for(int i = 0; i < size; ++i){
            cout << std::setw(6) << i;
            // printf("   %-3d",i);
        }
        cout << "\n    ";
        for(int i = 0; i < size; ++i){
            cout << "______";
        }
        for( int i = 0; i < size; ++i){
            cout << "\n" << std::setw(2) << i << " |";
            // printf("\n%2d |",i);
            for( int j = 0; j < size; ++j){
                cout << std::setprecision(2) << std::setw(6) << graph[i][j];
                // printf("  %-4d", graph[i][j]);
            }
        }
    }


private:

    // We need to know the number of nodes to properly size the connectivity matrix, and the unvisited and distance vectors
    int size;
    int edges;
    vector<vector<T>> graph;

    // the random number engine is defined as an attribute of the graph to avoid it "resetting" if using the randomize method repeatedly.
    default_random_engine generator;

};