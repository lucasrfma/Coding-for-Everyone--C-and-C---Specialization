/*     
    
    A Simple version of a Graph class, with minimal functionality for HexBoard to be implemented.

  Lucas Romero da F M de Andrade
  Start: feb. 17 2021
  End: feb. 20 2021
*/

// #include <cstdlib>
#include "SimpleGraph.h"
#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>

using std::vector;
using std::cout;
using std::endl;

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