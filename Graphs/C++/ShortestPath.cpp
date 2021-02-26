/*  This is a class to calculate the shortest path of a graph
    and a main function to test it and showcase it's functionality.
    
    Made for the week 3 Assignment for the course "C++ for C Programmers, Part A", University of California - Santa Cruz @ Coursera
    This was made following the Dijkstra's Shortest Path Algorithm as described in the wikipedia page:

      https://en.wikipedia.org/wiki/Dijkstra%27s_algorithm
      Algorithm section

  Lucas Romero da F M de Andrade
  Start: feb. 17 2021
  End: feb. 20 2021
*/

#include "Graph.cpp"
#include "PriorityQueue.cpp"
#include <iostream>
#include <vector>

class ShortestPath{

     public:

          typedef struct path{
               // path type: it has a vector that is used to describe a path, and an attribute that is the sum of the weights 
               // of every edge in that path.
               vector<int> path;
               float distance;
          }path;

          ShortestPath(Graph& graph):
          graph(graph),
          map(graph.Vertices()),
          visited(graph.Vertices(),vector<short>(graph.Vertices(),0))
          {}
          
          void setAllPaths(){
               /* Method that calls setPaths() for every node*/
               for( int i = 0; i < map.size(); ++i){
                    setPaths(i);
               }
          }

          void setPaths(int startNode){
               /* This method starts the calculating process for the row startNode of the map matrix.
                    The map matrix is a vector of path vectors. Each path represents the shortest path from
                    the row index to the column index.
               */
               // clear both queues to make them ready to calculate the distances from this starting node.
               seen.clear();

               // initialize the vector representing paths from StartNode
               map[startNode].resize(graph.Vertices());
               
               // Re-Initializes related path attributes
               for( int i = 0; i < graph.Vertices(); ++i){
                    map[startNode][i].distance = 0;
                    map[startNode][i].path.clear();
                    visited[startNode][i] = 0;
                    
               }
               
               // adds startNode to the seen queue.
               seen.addItem(startNode,0);

               // calculates the paths to other nodes
               calculatePaths(startNode);
          }

          vector<path> getPaths(int startNode){
               /* This method returns a vector that represents all the shortest paths from the startNode
                  to every other node in the graph.
               */

               // checks if it has not been calculated yet
               if( map[startNode].empty() ){
                    setPaths(startNode);
               }

              return map[startNode];
          }

          void printSeen(){
               /* Prints the Seen queue
                  Mostly for debugging purposes
               */
               seen.printQueue();
          }

          void printVisited(){
               /* prints the visited matrix (which represents all knows shortest paths) */
            
               cout << "\n    ";
               for(int i = 0; i < visited.size(); ++i){
                    printf("   %-2d",i);
               }
               cout << "\n    ";
               for(int i = 0; i < visited.size(); ++i){
                    printf("_____");
               }
               for( int i = 0; i < visited.size(); ++i){
                    printf("\n%2d |",i);
                    for( int j = 0; j < visited.size(); ++j){
                         printf("  %-3.1d", visited[i][j]);
                    }
               }
          }

          void printPath(int startNode, int endNode){
               printf(" Distance: %4.1f : Path: ",map[startNode][endNode].distance);
               for( int i = 0; i < map[startNode][endNode].path.size(); ++i ){
                    if( i == 0 ){
                         cout << map[startNode][endNode].path[i];
                    }else
                    {
                         cout << " -> " << map[startNode][endNode].path[i];
                    }
               }
               cout << endl;
          }

          void printPathsFrom(int startNode){
               cout << "\n";
               for( int i = 0; i < map[startNode].size(); ++i){
                    cout << startNode << " to " << i << ": ";
                    printPath(startNode,i);
                    cout << "\n";
               }
          }

          bool isConnected(){

               /* This method checks if the graph is connected.
                    It needs setPaths() to have been run at least once to work, so
                    if it hasn't been, this method itself will run getPaths(0) and
                    use recursion to return the appropriate bool value.
               */

               int sum;

               /* How it works:
                    Checks every row of visited and gets the sum of the columns. There can be 3 results with each iteration:
                    a ) If the sum is 0, it means getPaths() hasn't been run with the respective node as starting point
                    b ) If the sum is bigger than 0 and smaller than the number of nodes, it is not connected.
                    c ) If the sum is 10 it's connected.
                    Once b or c has happened, it will return true or false, and finish the method.
                    If the outer loop ends without reaching b or c, it will print an error message and return false*/

               for( int i = 0; i < visited.size(); ++i){
                    sum = 0;
                    for( int j = 0; j < visited[i].size(); ++j){
                         sum += visited[i][j];
                    }
                    if(sum == visited.size()){
                         return true;
                    } else if ( sum > 0 ){
                         return false;
                    }
               }
               // cout << "\nCan't determine if it's connected. Run setPaths() at least once and try again." << endl;
               setPaths(0);
               return isConnected();
          }

          float averagePathLength(int startNode){
               /* Returns the average path length of the paths to all nodes reachable from startNode*/
               float average = 0.0;
               int count = 0;
               for( int i = 0; i < map[startNode].size(); ++i){
                    if( i != startNode && visited[startNode][i] == 1 ){
                         ++count;
                         average +=  (map[startNode][i].distance - average)/count;
                    }
               }
               
               return average;
          }

          void averagePathLength(int startNode, float& average, int& count){
               /*   Calculates the average path length of the paths to all nodes reachable from startNode
                    This version uses average and count variables passed by reference.
                    This can be usefull if the user wants to know how many nodes are reachable from startNode
                    Or if calculating an average of path lengths from multiple startNodes, or even different graphs*/
               for( int i = 0; i < map[startNode].size(); ++i){
                    if( i != startNode && visited[startNode][i] == 1 ){
                         ++count;
                         average +=  (map[startNode][i].distance - average)/count;
                    }
               }    
          }

     private:

          Graph& graph;
          // visited is a matrix that represents all nodes that have been visited
          // eg: visited[0][1] == 0 means node 1 has not been visited starting from node 0 yet:
          //   If setPaths(0) has been run, and visited[0][1] is still 0, it means 1 is not reachable from 0
          //   If setPaths(0) has NOT been run, it is unknown whether it is reachable or not.
          // eg: visited[0][1] == 1 means node 1 has been visited, starting from node 0.
          vector<vector<short>> visited;
          // unvisited has all nodes already seen but not yet visited, as well as their best-so-far distance from the starting node
          PriorityQueue seen; 

          // this 2d matrix represents the shortest path from each node to each other node.
          vector<vector<path>> map;

          void addPath(int startNode, int visitingNode, int neighbor, float newPathDistance){
               /* this private method sets the path from startNode to neighbor node, going through visiting node*/

               // we clear the previous path
               map[startNode][neighbor].path.clear();
               // copy the path of the node being visited to its neighbors
               map[startNode][neighbor].path = map[startNode][visitingNode].path;
               // then add itself to the path
               map[startNode][neighbor].path.push_back(neighbor);
               // and assign to its distance newPathDistance
               map[startNode][neighbor].distance = newPathDistance;

               // add it to the seen queue
               seen.addItem(neighbor,newPathDistance); 
          }

          void calculatePaths(int startNode){

               int visitingNode;
               float visitingValue;
               float newPathDistance;
               vector<int> neighbors;

               // adds the startNode to it's own path.
               map[startNode][startNode].path.push_back(startNode);

               while(!seen.isEmpty()){

                    // first sorts the queue so the next item is the smallest of the seen queue.
                    seen.sort();

                    // 1 ) Visits next item from queue
                         // gets it's information and removes it from seen queue.
                    seen.popItem(visitingNode,visitingValue);

                    // if the new visiting node has been visited before, it is skipped
                    if( visited[startNode][visitingNode] == 1){
                         continue;
                    }

                    // 2 ) see what items are neighbors to the node being visited
                    // clears neighbors vector and populates it again from the Neighbors() of visitingNode
                    neighbors.clear();
                    neighbors = graph.Neighbors(visitingNode);

                    // 3 ) Analyse the distnces to the neighbors from the node being visited
                    for( int i = 0; i < neighbors.size(); ++i){
                         
                         // Only does anything to nodes not yet marked as visited
                         if( visited[startNode][neighbors[i]] == 0){
                              // Calculates the distance from startNode to the neighbors coming though visitingNode
                              newPathDistance = map[startNode][visitingNode].distance + graph.getEdgeValue(visitingNode,neighbors[i]);

                              // The new path is saved if:
                              // There wasn't a previous path, or
                              if( map[startNode][neighbors[i]].path.empty() ){
                                   addPath(startNode,visitingNode,neighbors[i],newPathDistance);
                              }
                              // the previous path is longer
                              else if( newPathDistance < map[startNode][neighbors[i]].distance ){
                                   addPath(startNode,visitingNode,neighbors[i],newPathDistance);
                              }
                         }
                    }
                    // marks the visitingNode as visited
                    visited[startNode][visitingNode] = 1;
               }

          }
};