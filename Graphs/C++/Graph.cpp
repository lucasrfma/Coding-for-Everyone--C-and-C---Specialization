/*     
    For the graph representation as a data structure I decided to use a square matrix created by a 2d vector. 
    Although making it a square matrix means it will take up more memory than a vector of differently sized vectors, 
    it also is, in my opinion, easier to think about and understand,
    so it should result in simpler and faster algorithms.

  Made for the week 3 Assignment for the course "C++ for C Programmers, Part A", University of California - Santa Cruz @ Coursera
  Lucas Romero da F M de Andrade
  Start: feb. 17 2021
  End: feb. 20 2021
*/

#include <iostream>
#include <cstdlib>
#include <chrono>
#include <vector>
#include <random>

using namespace std;

class Graph{

    public:

        Graph(int size = 10, float maxDistance = 1000000):size(size), edges(0), graph(size,vector<float>(size,0.0)), maxDistance(maxDistance){
            
            // initializes the generator to be used in RandomizeGraph() method.
            unsigned seed = chrono::system_clock::now().time_since_epoch().count();
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
            return ( graph[node1][node2] > 0.0 );
        }

        vector<int> Neighbors(int node){
            // returns a vector of ints indicating which nodes have edges with the specified node.
            vector<int> neighbors;

            for( int i = 0; i < size; ++i){
                if( graph[node][i] > 0){
                    neighbors.push_back(i);
                }
            }

            return neighbors;
        }

        void addEdge(int node1, int node2, float distance){
            // adds an edge with the specified weight/distance between the specified nodes
            // only does anything if the edge really did not exist.
            if( !Adjacent(node1,node2) ){
                graph[node1][node2] = graph[node2][node1] = distance;
                ++edges;
            }
        }

        void deleteEdge(int node1, int node2){
            // removes the edge between the specified nodes
            // only does anything if the edge really exists.
            if( Adjacent(node1,node2)){
                graph[node1][node2] = graph[node2][node1] = 0;
                --edges;
            }
        }

        float getEdgeValue(int node1, int node2){
            // returns the weight/distance of the edge between specified nodes
            return graph[node1][node2];
        }

        void setEdgeValue(int node1, int node2, float value){
            // changes the weight/distance of an existing edge
            // to avoid misuse, this method checks if deleteEdge or addEdge aren't the proper methods before actually changing the value.
            if( !Adjacent(node1,node2) ){
                addEdge(node1,node2,value);
            }else if( value == 0){
                deleteEdge(node1,node2);
            }else{
                graph[node1][node2] = graph[node2][node1] = value;
            }
        }

        void randomizeGraph( const float density = 0.2, const float minDistance = 1.0, const float maxDistance = 10.0){
            // This function creates randomized edges on the graph.
            // The user can specify density, as well as the minimum and maximum edge weight/distance
            // If no arguments are specified, the density will be of 20%, minimum distance of 1.0 and maximum of 10.0

            this->maxDistance = maxDistance;

            // to decide if there is or there is not an edge between 2 nodes
            uniform_real_distribution<double> rollEdgePresence(0.0,1.0);
            // to decide the size of an edge.
            uniform_real_distribution<double> rollDistance(minDistance,maxDistance);

            for(int i = 0; i < size; ++i){
                for(int j = 0; j < size; ++j){
                    // no loop edges, so we do nothing when i == j
                    // since the edges are bidirectional, graph[i][j] should be equal to graph[j][i]. addEdge() already sets both ways.
                    // so we only do anything when j > i.
                    if ( j > i){
                        if( rollEdgePresence(generator) < density ){
                            addEdge(i,j,rollDistance(generator));
                        }
                    }
                }
            }
        }

        void printGraph(){
            // prints a table representing the graph
            
            cout << "\n    ";
            for(int i = 0; i < size; ++i){
                printf("   %-3d",i);
            }
            cout << "\n    ";
            for(int i = 0; i < size; ++i){
                printf("______");
            }
            for( int i = 0; i < size; ++i){
                printf("\n%2d |",i);
                for( int j = 0; j < size; ++j){
                    printf("  %-4.1f", graph[i][j]);
                }
            }
        }

        float getMaxDistance(){
            // returns the maximum weight/distance of an edge.
            // can be usefull when defining the "infinity" used in the algorithm description at the head of this file.
            return maxDistance;
        }

    private:

        // We need to know the number of nodes to properly size the connectivity matrix, and the unvisited and distance vectors
        int size;
        int edges;
        vector<vector<float>> graph;

        float maxDistance;
        // the random number engine is defined as an attribute of the graph to avoid it "resetting" if using the randomize method repeatedly.
        default_random_engine generator;

};