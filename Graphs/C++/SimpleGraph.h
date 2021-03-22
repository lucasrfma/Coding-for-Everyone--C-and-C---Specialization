#ifndef _GRAPH
#define _GRAPH

#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>

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

#endif