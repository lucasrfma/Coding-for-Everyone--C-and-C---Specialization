/*

This is a main function to showcase much of the functionality of the classes Graph.cpp, PriorityQueue.cpp and ShortestPath.cpp

It's output is just what I understood as necessary per the instructions of the exercise.

Made for the week 3 Assignment for the course "C++ for C Programmers, Part A", University of California - Santa Cruz @ Coursera
  Lucas Romero da F M de Andrade
  feb. 20 2021

*/


#include "ShortestPath.cpp"
#include <iostream>
#include <vector>

using namespace std;

int main(){

    const int nodes = 50;
    const int sampleSize = 1000;

    int startNode = 0;
    float average;
    int count;
    // create a graph of 50 nodes
    Graph graph(nodes);
    ShortestPath navigator(graph);

    // Calculate average of shortest paths for 50 random graphs, starting from every node to every other node.
    average = 0.0;
    count = 0;
    for(int i = 0; i < sampleSize; ++i ){
        // call randomize using default values: 
        // density = 20%
        // minDistance = 1.0
        // maxDistance = 10.0
        graph.randomizeGraph(0.2);
        navigator.setPaths(startNode);
        navigator.averagePathLength(startNode,average,count);
        // for( startNode = 0; startNode < nodes; ++startNode){
        //     navigator.averagePathLength(startNode,average,count);
        // }
    }

    printf("\n\nNumber of graphs generated: %d\nNumber of nodes in each graph: %d\n",sampleSize,nodes);
    printf("\nThe average of the shortest paths in the 20%% edge density graph is %.3f",average);
    printf("\nPath count : %d",count);

    // Now the same for a density of 40%
    average = 0.0;
    count = 0;
    for(int i = 0; i < sampleSize; ++i ){
        graph.randomizeGraph(0.4);
        navigator.setPaths(startNode);
        navigator.averagePathLength(startNode,average,count);
        // for( startNode = 0; startNode < nodes; ++startNode){
        //     navigator.averagePathLength(startNode,average,count);
        // }
    }

    printf("\n\nThe average of the shortest paths in the 40%% edge density graph is %.3f",average);
    printf("\nPath count : %d",count);



    return 0;
}