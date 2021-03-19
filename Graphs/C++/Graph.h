#ifndef _GRAPH
#define _GRAPH

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

    Graph();
    Graph(int size);

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
    T getEdgeValue(int node1, int node2);

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
    void randomizeGraph();
    void randomizeGraph( const double density, const T minDistance, const T maxDistance);

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

#include "Graph.tpp"

#endif