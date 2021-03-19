/*

This is a main function to showcase much of the functionality of the classes Graph.cpp, PriorityQueue.cpp and ShortestPath.cpp

It's output is quite big, but is interesting, at least to me, as it enables the viewer to check if the program
is truly working as intended.

Made for the week 3 Assignment for the course "C++ for C Programmers, Part A", University of California - Santa Cruz @ Coursera
  Lucas Romero da F M de Andrade
  feb. 20 2021

*/


#include "ShortestPath.cpp"
#include <iostream>
#include <vector>

using namespace std;

template<typename T>
void printInfoFrom(ShortestPath<T>& navigator, int startNode){
    double average = 0.0;
    int count = 0;
    printf("\n-----------------------------------------------"
            "\nAll paths starting from node %d:\n",startNode);
    navigator.printPathsFrom(startNode);

    navigator.averagePathLength(startNode,average,count);
    printf("Nodes reachable from node %d excluding itself: %d\n",startNode,count);
    printf("Average path distance: %.1f",average);
}

int main(){

    int startNode = 0, count;
    float average;
    // create a graph of size 50
    Graph<int> graph(20);

    // call randomize using default values: 
    // density = 0.2
    // minDistance = 1.0
    // maxDistance = 10.0
    graph.randomizeGraph();

    ShortestPath<int> navigator(graph);

    printf("\n\nGraph (20%% density):\n");

    graph.printGraph();

    navigator.setAllPaths();

    printf("\nConnectivity matrix: \n(1 = column node is reachable from row node)\n");

    // navigator.printVisited();

    if( navigator.isConnected()){
        cout << "\n\nAll nodes are reachable!";
    }else{
        cout << "\n\nThere are unreachable nodes.";
    }
    
    printInfoFrom(navigator,startNode);

    return 0;
}