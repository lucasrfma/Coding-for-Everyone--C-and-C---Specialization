/*

Minimum Spanning Tree following the Prim Algorithm

Lucas Romero da F. M. de Andrade
feb. 24 2021

*/

#include "Graph.cpp"
#include "PriorityQueue.cpp"
#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

class MinimumSpanningTree{

    private:

        const float notConnected = 2000000.0;
        const int rootConnection = -1;
        const float rootDistance = -1.0;

        struct Edge{
            int connectedTo;
            float distance;
        };

        struct Node{
            Edge previous;
            vector<Edge> branches;
        };

        vector<Node> tree;
        vector<bool> visited;   // a vector that represents visited nodes. Visited nodes are not to be revisited
        PriorityQueue seen;     // PriorityQueue saves and sorts all seen nodes. 
                                // When a node is visited, it's edges are added to the seen queue.

        Graph& graph;          
        int size;
        int start;

        void resetTree(int size = 0){
            /*
            private function that reinitializes the object's attributes
            */

            // in case size has not been passed, resize isn't called
            if( size != 0){
                tree.resize(size);
                visited.resize(size);
                this->size = size;
            }
            for(int i = 0; i < this->size; ++i){
                tree[i].previous.distance = notConnected;
            }
            visited.assign(this->size,false);
            seen.clear();
        }

        void setPreviousEdge(int node, int previousNode, float distance){
            tree[node].previous.connectedTo = previousNode;
            tree[node].previous.distance = distance;
        }

        void addAsBranch(int branch){
            /* adds 'branch' to branches vector of 'node'
               of it's 'previous' edge, unless it's previous edge == rootConnection
            */
            // Get's previous node's index
            int previous = tree[branch].previous.connectedTo;

            // creates the branch to be added to the previous node.
            Edge newBranch;
            newBranch.connectedTo = branch;
            // connections here are 2 way, so distance from previous to branch is the same as from branch to previous
            newBranch.distance = tree[branch].previous.distance; 

            if( previous != rootConnection ){
                tree[previous].branches.push_back(newBranch);
            }
        }

        void buildTree(){
            /*
            Builds the Tree. Steps to do that:

            1 ) set previous edge for the starting node. Add it to seen queue

            2 ) loop = while there is a node in the seen Queue.
                3 ) sort seen PriorityQueue
                4 ) take node from the seen PriorityQueue (call it visiting)
                    4-b) Continues to next iteration if this node has been marked as visited.
                5 ) Get node's neighbors
                6 ) Set neighbor's 'previous' edge to visiting node if:
                    a ) distance from visiting to neighbor is smaller than that neighbor's 'previous' Edge
                    b ) there is no current 'previous' edge
                    7 ) Add neighbor to seen PriorityQueue if it's 'previous' edge was changed.
                8) marks visiting as visited
                9) Add visiting as a branch of it's previous node
            */
            // 1, as seen above
            setPreviousEdge(start,rootConnection,rootDistance);   
            seen.addItem(start,0.0);

            int visiting;
            float distance;
            vector<int> neighbors;

            // 2
            while(!seen.isEmpty()){

                // 3 and 4
                seen.sort();
                seen.popItem(visiting);
                // 4-b
                if( visited[visiting] == true){
                    continue;
                }

                // 5
                neighbors.clear();
                neighbors = graph.Neighbors(visiting);

                // std::cout << "Visiting: " << visiting << "  " << tree[visiting].previous.distance << "\n";
                for( int i = 0; i < neighbors.size(); ++i){
                    if( !visited[neighbors[i]]){
                        // std::cout << "Neighbor: " << neighbors[i] << "  " << tree[neighbors[i]].previous.distance << " -> ";
                        // 6 a) and b)
                        // "no current previous edge value" is represented by notConnected, 
                        // which is a really large number defined above, so both cases share the same test
                        // std::cout << visiting << " " << neighbors[i] << " " << graph.getEdgeValue(visiting,neighbors[i]) << " -> ";
                        distance = graph.getEdgeValue(visiting,neighbors[i]);
                        // std::cout << distance << "\n";
                        // std::cout << tree[neighbors[i]].previous.distance << "\n";
                        if( tree[neighbors[i]].previous.distance > distance ){
                            tree[neighbors[i]].previous.connectedTo = visiting;
                            tree[neighbors[i]].previous.distance = distance;
                            seen.addItem(neighbors[i],distance);
                        }
                        // std::cout << "After : Neighbor: " << neighbors[i] << " <- " << tree[neighbors[i]].previous.connectedTo << "  " << tree[neighbors[i]].previous.distance << "\n";
                    }
                }
                // 8 and 9
                visited[visiting] = true;
                addAsBranch(visiting);
            }

        }

        void printTree(int node, int fromStart){
            /*  This method "draws" the tree to the terminal 
             *  It has 2 versions, one private and one public. This is to make the calling of the function easier.
             *  The public version has no arguments while the private one has arguments needed for the recursion to work
             *  PS: it's made to look nice if the nodes go from 0 to 99. with 3digit+ nodes it will become skewed
             *      This can be changed by tweaking the setw() function on the cout. 
             *          (but if you change, remember to change in both versions!)
             */
            string spacing = "";
            for( int i = 0; i < fromStart; ++i){
                spacing = spacing + "      ";
            }
            spacing = spacing + "     |";

            std::cout << "--> " << setw(2) << node;
            
            for( int i = 0; i < tree[node].branches.size() ; ++i){
                if( i > 0 ){
                    std::cout << std::endl << spacing;
                }
                printTree(tree[node].branches[i].connectedTo,fromStart+1);
            }
        }

    public:

        MinimumSpanningTree(Graph& graph, int start = 0):
            graph(graph),
            start(start),
            seen(){
                size = graph.Vertices();
                resetTree(size);
                buildTree();
            }


        void setGraph(Graph& graph){
            /*
            In case there is a need to change the graph to be worked on
            */
            this->graph = graph;
            size = graph.Vertices();
            resetTree(size);
            buildTree();
        }

        void setStart(int start){
            this->start = start;
            resetTree();
            buildTree();
        }

        vector<Node> getTree(){
            /*
            Returns the tree
            */
           return tree;
        }

        int getStart(){
            return start;
        }

        void printTreeList(){
            /**
             * Prints the tree as a list of nodes
             */
            
            for(int i = 0; i < tree.size(); ++i){
                std::cout << "Node: " << i << " Branches: ";
                for(int j = 0; j < tree[i].branches.size() ; ++j){
                    std::cout << tree[i].branches[j].connectedTo << ", ";
                }
                std::cout << std::endl;
            }
        }

        void printTree(){
            /*  This method "draws" the tree to the terminal 
             *  It has 2 versions, one private and one public. This is to make the calling of the function easier.
             *  The public version has no arguments while the private one has arguments needed for the recursion to work
             *  PS: it's made to look nice if the nodes go from 0 to 99. with 3digit+ nodes it will become skewed
             *      This can be changed by tweaking the setw() function on the cout.
             */
            int node = 0, fromStart;
            fromStart = start;

            string spacing = "";
            for( int i = 0; i < fromStart; ++i){
                spacing = spacing + "      ";
            }
            spacing = spacing + "     |";

            std::cout << "root" << setw(2) << node;
            for( int i = 0; i < tree[node].branches.size() ; ++i){
                if( i > 0 ){
                    std::cout << std::endl << spacing;
                }
                printTree(tree[node].branches[i].connectedTo,fromStart+1);
            }
        }

};

int main(){
    
    const int nodes = 20;

    int startNode = 0;

    Graph graph(nodes);
    // to test with random graph
    graph.randomizeGraph(0.5);

    // to test with the graph from video 4.4 Kruskal simulate 
    // (because I liked the graphical representation of the graph in that video)
    // vector<vector<float>> newGraph = {  {0.0, 7.0, 0.0, 5.0, 0.0, 0.0, 0.0},
    //                                     {7.0, 0.0, 8.0, 9.0, 7.0, 0.0, 0.0},
    //                                     {0.0, 8.0, 0.0, 0.0, 5.0, 0.0, 0.0},
    //                                     {5.0, 9.0, 0.0, 0.0, 15.0,6.0, 0.0},
    //                                     {0.0, 7.0, 5.0,15.0, 0.0, 8.0, 9.0},
    //                                     {0.0, 0.0, 0.0, 6.0, 8.0, 0.0,11.0},
    //                                     {0.0, 0.0, 0.0, 0.0, 9.0,11.0, 0.0}};
    // graph.setGraph(newGraph);

    graph.printGraph();
    MinimumSpanningTree tree(graph);

    printf("\n\nMinimum Spanning Tree drawn:\n\n");
    tree.printTree();
    printf("\n\nMinimum Spanning Tree as a list of nodes:\n\n");
    tree.printTreeList();

}