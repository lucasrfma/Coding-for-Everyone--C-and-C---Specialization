#pragma once

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

#include <iostream>
#include <iomanip>
#include <vector>
#include <chrono>
#include <random>
#include <fstream>
#include <iterator>
#include <type_traits>

template <typename T>
class Graph{
public:

    Graph(int size = 10);

    /**
     * Constructor that makes the graph from an existing 2d vector.
     */
    Graph(const std::vector<std::vector<T>>& newGraph);

    /**
     * Constructor that makes the graph from file.
     * The file format will be an initial integer that is the node size of the graph
     * and the further values will be: (i, j, cost). 
     * where i and j are integers that define the nodes, and cost is the edge weight
     */
    Graph(std::string file_name);

    /**
     * Method for seeding the pseudo random number generator used in randomizeGraph()
     */
    void seedRandomNumberGen();

    // returns the number of vertices
    int Vertices();

    // returns the number of edges
    int Edges();

    // returns true if there is an edge between the nodes
    bool Adjacent(int node1, int node2);

    /**
     * returns a vector of ints indicating which nodes have edges with the specified node.
     */
    std::vector<int> Neighbors(int node);

    /**
     * adds an edge with the specified weight/distance between the specified nodes
     * only does anything if the edge really did not exist.
     */
    void addEdge(int node1, int node2, T distance);

    /**
     * removes the edge between the specified nodes
     * only does anything if the edge really exists.
     */
    void deleteEdge(int node1, int node2);

    /**
     * returns the weight of the edge between specified nodes
     */
    T getEdgeValue(int node1, int node2){
        return graph[node1][node2];
    }

    /**
     * changes the weight/distance of an existing edge
     * to avoid misuse, this method checks if deleteEdge or addEdge aren't
     * the proper methods before actually changing the value.
     */
    void setEdgeValue(int node1, int node2, T value);

    /**
     * This function creates randomized edges on the graph.
     * The user can specify density, as well as the minimum and maximum edge weight/distance
     * If no arguments are specified, the density will be of 20%, minimum distance of 1.0 and maximum of 10.0
     */
    void randomizeGraph( const double density = 0.2, const T minDistance = static_cast<T>(1.0), const T maxDistance = static_cast<T>(10.0));

    /**
     * prints a table representing the graph
     */
    void printGraph();


private:

    // We need to know the number of nodes to properly size the connectivity matrix, and the unvisited and distance vectors
    int size;
    int edges;
    std::vector<std::vector<T>> graph;

    // the random number engine is defined as an attribute of the graph to avoid it "resetting" if using the randomize method repeatedly.
    std::default_random_engine generator;

};