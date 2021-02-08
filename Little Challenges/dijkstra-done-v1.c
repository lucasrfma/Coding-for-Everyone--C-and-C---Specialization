/*
Try to implement Dijkstra Shortest Path algorithm using C

I haven't seen how dijkstra works, only the outline: 

1. Create an Open Set with the current shortest path to each node
2. As we make sure we found the absolute shorted path to each node, they are added to the ClosedSet
3. Once the Destination/End is added to the closed path, the program ends (or once we find that it's impossible to reach it)

Start Date: 02/07/2021
End Date:   02/08/2021

Test graph (S = Start; E = End):

       S  A  B  C  D  E
    S  0  1  2  3  -  -  
    A  1  0  2  -  2  -
    B  2  2  0  1  2  4 
    C  3  -  1  0  3  1
    D  -  2  2  3  0  2
    E  -  -  4  1  2  0
*/

#include <stdio.h>
#define N_NODES 6

typedef enum cities{ START, A, B, C, D, END }cities;

typedef struct node{
    int links[N_NODES];         // a vector representing direct connections
    int openPath[N_NODES];      // a vector representing the current path to this node
    char isClosed;              // flag that marks a closed node
    int openPathSize;           // the sum of the distances in the current path
    int possibilities;          // This will be the number of links to the node, excluding from links from END
    char passThru;              // flag that raised upon a openPaths() call on the node
}node;

void graphInitializer(node graph[]){

    int i,j;
                                              //S   A   B   C   D   E        Links from
    int DISTANCES[N_NODES][N_NODES] =       { { 0,  1,  2,  3, -1, -1},  //S
                                              { 1,  0,  2, -1,  2, -1},  //A
                                              { 2,  2,  0,  1,  2,  4},  //B
                                              { 3, -1,  1,  0,  3,  1},  //C
                                              {-1,  2,  2,  3,  0,  2},  //D
                                              {-1, -1,  4,  1,  2,  0}}; //E

    // // Different test values
    //                                           //S   A   B   C   D   E        Links from
    // int DISTANCES[N_NODES][N_NODES] =       { { 0, -1, -1,  3, -1, -1},  //S
    //                                           {-1,  0,  1,  1, -1, -1},  //A
    //                                           {-1,  1,  0, -1,  2, -1},  //B
    //                                           { 3,  1, -1,  0, -1, -1},  //C
    //                                           {-1, -1,  2, -1,  0,  2},  //D
    //                                           {-1, -1, -1, -1,  2,  0}}; //E
    
    // // Testing one way routes
    //                                           //S   A   B   C   D   E        Links from
    // int DISTANCES[N_NODES][N_NODES] =       { { 0,  1,  2,  3, -1, -1},  //S
    //                                           {-1,  0,  2, -1,  2, -1},  //A
    //                                           {-1, -1,  0,  1,  2,  4},  //B
    //                                           {-1, -1, -1,  0,  3,  1},  //C
    //                                           {-1, -1, -1, -1,  0,  2},  //D
    //                                           {-1, -1, -1, -1, -1,  0}}; //E
    
    // Testing impossible destination
    //                                           //S   A   B   C   D   E        Links from
    // int DISTANCES[N_NODES][N_NODES] =       { { 0,  1,  2,  3, -1, -1},  //S
    //                                           {-1,  0,  2, -1,  2, -1},  //A
    //                                           {-1, -1,  0,  1,  2, -1},  //B
    //                                           {-1, -1, -1,  0,  3, -1},  //C
    //                                           {-1, -1, -1, -1,  0, -1},  //D
    //                                           {-1, -1, -1, -1, -1,  0}}; //E

    // Node initialization = copying the contents of the matrix graph representation into the node vector.
    for( i = START; i <= END; i++)
        for( j = START; j <= END; j++)
            graph[i].links[j] = DISTANCES[i][j];

    // Node initialization = There are still no paths to the nodes other than S!
    for( i = START; i <= END; i++){
        // S is the start, so we have the closed path already!
        if( i == START){
            graph[i].isClosed = 1;  // isClosed will be used as a boolean of sorts. 1 = true = is closed, 0 = false = isnt closed
            graph[i].openPathSize = 0;
            graph[i].possibilities = 0;
            graph[i].passThru = 0;
            for( j = START; j <= END; j++){
                graph[i].openPath[j] = 0;
            }
        }else{ // Other nodes are not analyzed yet, so we set the path sizes to -1 to indicate "no path yet"
            graph[i].isClosed = 0;
            graph[i].openPathSize = -1;
            graph[i].passThru = 0;
            // This part we count the possibilities to reach each node (excluding from END)
            for( j = START, graph[i].possibilities = 0; j < END; j++){
                // if a graph[j].links[i] is positive, it means there is a path from the node j to the node i
                if( graph[j].links[i] > 0)
                    graph[i].possibilities++;
            }
        }
    }

}

int setPath(node graph[], int baseNode, int thisNode){
    /*
    This function copies the path of the base node to thisNode, then adds the base node as the last step of the path to thisNode.

    Then it adds the distance from baseNode to thisNode's pathSize and assigns it to thisNode's pathSize, and returns it.
    */
    int i,lastStep = 0;

    for( i = START; i <= END; i++){
        if( (graph[thisNode].openPath[i] = graph[baseNode].openPath[i]) > lastStep )
            lastStep = graph[thisNode].openPath[i];
    }
    graph[thisNode].openPath[baseNode] = lastStep + 1;

    return (graph[thisNode].openPathSize = graph[baseNode].openPathSize + graph[baseNode].links[thisNode]);

}

int openPaths(node graph[], int currentNode){
    /*
    This function receives the graph vector and the identifier of the node being worked
    It then checks if the nodes linked to this one have paths:
    If they don't, it opens a path to them from this one
    If they do but it's longer than going from this node, the path is updated
    If they do and their current path is better or equal to the one coming by this node, it stays the same
     
    Either way it will always do two things:
    1 - Return the identifier of the closest node to this node
        - Returns -1 in case there are no linked nodes outside it's current path
    2 - Reduce the 'possibilities' counter on the linked nodes by 1*/
    
    int comparisonNode, smallest = -1;

    for( comparisonNode = START; comparisonNode <= END; comparisonNode++){

        // Will only do something if comparisonNode isn't already closed
        if( !(graph[comparisonNode].isClosed) ){

            // Checks for linked notes
            if(graph[currentNode].links[comparisonNode] > 0){ 
                // checks if the node is in the current path already
                if(graph[currentNode].openPath[comparisonNode] == 0){// Must not be on path!!
                    
                    // Now we check for 2 possibilities:
                    // 1 ) comparisonNode hasn't opened yet
                    // 2 ) comparisonNode's current pathSize is bigger that currentNode's path+distance to comparisonNode
                    if( (graph[comparisonNode].openPathSize == -1) || 
                        (graph[currentNode].openPathSize+graph[currentNode].links[comparisonNode] < graph[comparisonNode].openPathSize)  ){
                        // If any of these conditions were met, it means the path through currentNode is, so far, the best path to comparisonNode
                        // It also checks if the new path is the smallest path stemming from the currentNode. If it is, smallest will be updated to indicate this iteration's comparisonNode
                        if(graph[smallest].openPathSize > setPath(graph,currentNode,comparisonNode) || smallest == -1 ){
                            smallest = comparisonNode;
                        }
                    }
                    
                }// the possibilities for reaching comparisonNode have diminished by 1, so we update that attribute, and close it if possibilities becomes 0   
                if( !(--graph[comparisonNode].possibilities) ){
                    graph[comparisonNode].isClosed = 1;
                }
            }
        }
    }
    graph[currentNode].passThru = 1;
    return smallest;
}

void printNode(node *nd){
    int i,j;
    printf("\nIs closed: %d\n"
           "Open Path Size: %d\n"
           "Possibilities: %d\n"
           "Path: ",nd->isClosed,nd->openPathSize,nd->possibilities);
    for( i = 1; i <= END; i++){
        for( j = START; j <= END; j++){
            if( nd->openPath[j] == i)
                printf("\t%d",j);
        }
    }
    printf("\n");
}

int main(){
    //Iterators
    int i,j, newOpenings;
    // Represents the Open Distances. Only Positive Distances really matter: when a distance smaller than all open distances is found, it's the closed path to that node
    int openDistances[N_NODES] = {0,-1,-1,-1,-1,-1};

    // a vector of nodes. Used to save the state of each node
    node graph[N_NODES];

    // initializes various attributes
    graphInitializer(graph);

    // while the shortest path to E is unkown (and it's not been confirmed that there is no path to E), the program should run.
    while( !(graph[END].isClosed) ){

        // newOpenings will mark if there were any changes in a while iteration. If there weren't any, the while stops due to impossibility to move reach destination
        newOpenings = 0;
        for( i = START; i <= END; i++){
            // we call the openPaths() functions on every node that hasn't yet passed through it, but has already been reached by other passes
            if( graph[i].openPathSize != -1 && !graph[i].passThru ){

                // this printf was made to separate the prints from the loop below in groups
                // printf("\n--%d-----",i);
                openPaths(graph,i);
                newOpenings++;

                // //this loop was made to check the changes throughout iterations
                // for(j = START; j <= END; j++){
                //     printf("\n%d",j);
                //     printNode(&graph[j]);
                // }
            }
        }
        if( !newOpenings ){
            printf("\n\nImpossible to reach destination!!\n\n");
            break;
        }
    }

    if( graph[END].isClosed ){
        printf("\n\n");
        printNode(&graph[END]);
        printf("\n\n");
    }
    return 0;
}