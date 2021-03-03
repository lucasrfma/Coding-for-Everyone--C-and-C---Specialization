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
#include <fstream>
#include <iterator>

using namespace std;

class Graph{

    public:

        Graph(int size = 10, int maxDistance = 1000000):size(size), edges(0), graph(size,vector<int>(size,0)), maxDistance(maxDistance){
            
            // initializes the generator to be used in RandomizeGraph() method.
            unsigned seed = chrono::system_clock::now().time_since_epoch().count();
            generator.seed(seed);
        }

        Graph(std::string file_name): maxDistance(1000000),edges(0){
            /**
             * Constructor that makes the graph from file.
             * The file format will be an initial integer that is the node size of the graph
             * and the further values will be integer triples: (i, j, cost). 
             */
            std::ifstream input_file(file_name);
            std::istream_iterator<int> start(input_file), end; // create iterators
            std::vector<int> graphData(start,end);             // use iterators to create an int vector with all the file data

            size = graphData[0];    // The first element determines the node size of the graph
            graph.resize(size,vector<int>(size,0)); // initialize the graph with the size read, all nodes unconnected

            // this loop will go through the ints read, starting from the second (since the first was the node size)
            // each iteration increases by 3, since each edge is an int triple.
            for( int i = 1; i < graphData.size(); i += 3){
                            //i                j                                cost
                addEdge( graphData[i] , graphData[i+1], static_cast<int>(graphData[i+2]));
            }
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
            return ( graph[node1][node2] > 0 );
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

        void addEdge(int node1, int node2, int distance){
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

        int getEdgeValue(int node1, int node2){
            // returns the weight/distance of the edge between specified nodes
            return graph[node1][node2];
        }

        void setEdgeValue(int node1, int node2, int value){
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

        void randomizeGraph( const float density = 0.2, const int minDistance = 1, const int maxDistance = 10){
            // This function creates randomized edges on the graph.
            // The user can specify density, as well as the minimum and maximum edge weight/distance
            // If no arguments are specified, the density will be of 20%, minimum distance of 1.0 and maximum of 10.0

            this->maxDistance = maxDistance;

            // to decide if there is or there is not an edge between 2 nodes
            std::uniform_real_distribution<double> rollEdgePresence(0.0,1.0);
            // to decide the size of an edge.
            std::uniform_int_distribution<int> rollDistance(minDistance,maxDistance);

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
                    printf("  %-4d", graph[i][j]);
                }
            }
        }

        int getMaxDistance(){
            // returns the maximum weight/distance of an edge.
            // can be usefull when defining the "infinity" used in the algorithm description at the head of this file.
            return maxDistance;
        }

        void setGraph(const vector<vector<int>>& newGraph){
            graph.clear();
            graph = newGraph;
            size = graph.size();
            edges = 0;
            for( int i = 0; i < graph.size(); ++i ){
                for( int j = 0; j < graph[i].size(); ++j){
                    if( graph[i][j] > 0 ){
                        ++edges;
                    }
                }
            }
        }

    private:

        // We need to know the number of nodes to properly size the connectivity matrix, and the unvisited and distance vectors
        int size;
        int edges;
        vector<vector<int>> graph;

        int maxDistance;
        // the random number engine is defined as an attribute of the graph to avoid it "resetting" if using the randomize method repeatedly.
        default_random_engine generator;

};