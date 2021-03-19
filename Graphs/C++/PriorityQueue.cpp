/*  This is a priority queue class to be used in conjunction with a shortestPath class and a Graph class
    for the week 3 Assignment for the course "C++ for C Programmers, Part A", University of California - Santa Cruz @ Coursera

    This PriorityQeue class makes it easy to create an ordered queue. This queue will be made of a vector of items.
    Items is a data structure defined below. More details inside its definition

    Lucas Romero da F M de Andrade
    Start: feb. 17 2021
    End: feb. 20 2021

    
    mar. 6 2021:
        Changed to be a template. It should work properly with either integer or floating point types.
*/

#include<iostream>
#include<vector>

using namespace std;

template<typename T>
class PriorityQueue{

public:

    PriorityQueue(){}
    
    typedef struct item{
        /*  This data strucure has 2 attributes: identifier and value
            identifier is the "name" of each element, while value is it's weight/distance/value

            The queue is to be sorted by value. The sorting is biggest to smallest.
            The name is important as it is what makes it possible to recognize the nodes of the related class Graph.
        */
        int identifier;
        T value;
    }item;

    void addItem(int identifier, T value){
        // adds an item to the queue.
        item nItem;
        nItem.identifier = identifier;
        nItem.value = value;
        this->queue.push_back(nItem);
    }

    void popItem(int& identifier, T& value){
        /**
         * receives two variables as Pass by Reference.
         * saves the values of the last item in the queue into these variables
         * removes the last item in the queue
         */
        identifier = queue[queue.size()-1].identifier;
        value = queue[queue.size()-1].value;
        queue.pop_back();
    }
    void popItem(int& identifier){
        /**
         * saves the identifier of the last item in the queue into the variable received as an argument
         * removes the last item in the queue
         */
        identifier = queue[queue.size()-1].identifier;
        queue.pop_back();
    }

    void addItemSorted(int identifier, T value){
        /**
         * adds an item to the queue, and sorts the queue.
         */
        item nItem;
        nItem.identifier = identifier;
        nItem.value = value;
        this->queue.push_back(nItem);

        sort();
    }

    int getSize(){
        /**
         * returns the size of the queue
         */
        return queue.size();
    }

    bool isEmpty(){
        /* returns true if queue is empty */
        return queue.empty();
    }

    void printQueue(){
        /**
         * prints the current queue. Remember, this queue is made so the Last Item is always the one to be removed.
         * It should, normally, be sorted before being popped so the last element is the smallest one
         */
        cout << "\n";
        for( int i = 0; i < queue.size() ; ++i){
            cout << queue[i].identifier << ": " << queue[i].value << "   ";
        }
        cout << endl;
    }
    
    void clear(){
        queue.clear();
    }

    void sort(){

        /* This function is responsible for using the mergeSort correctly to sort a single array.
            In this, i determines the start of each subsection passed to the mergeSort function.
            Each subsection is divided in 2 parts. 
            
            The first part starts at i, and has a length of k.
            The second part starts at i+k, and has the length of the smaller of:
                a) k;
                b) length of original array subtracted i+k.

            k starts at 1, since the original array is completely unsorted, we can't assume anything bigger than a single value is properly sorted.
            From there, k increases in power of 2: 
                The first passthrough with k=1 guarantees each pair ( 0,1 ; 2,3 ; 4,5 ...) is sorted.
                Thus the second passthrough will divide the original array into previously sorted arrays of 2 elements each, passing these as arguments to mergeSort();
                Which means, for the third passthrough, every sequence of 4 elements is already sorted, now 4 is the length of each subsection, and so on.
                
                The aforementioned b) case is intended to cater to arrays with lenghts different than any power of 2.

            The scattered printf's were used for debugging.
            
        */

        int i,j,k;
        
        for ( k = 1; k < queue.size(); k*=2 ){
            for( i = 0; i < queue.size(); i += 2*k){
                if( i + 2*k > queue.size()){
                    if( queue.size() > (i+k) ){
                        mergeSort(i,k,queue.size() - (i+k));
                    }
                }else
                {
                    mergeSort(i,k,k);
                }                  
            }
        }
    }

    private:

        vector<item> queue;

        void mergeSort(int start,int size1, int size2){
            // treats 2 sections of an array as 2 separate ordered arrays, and puts all their elements in order back into the original array, starting at the point indicated by the first argument
            // this is an internal method that becomes useful in tandem with the public method sort(). 
            // sort() acts as the manager this method needs to actually sort a completely unsorted queue.
        
            int i=0,j=0,k=0;
            item tempArray[size1+size2];
            
            while( i < size1 && j < size2 ){
                if(queue[start+i].value > queue[start+size1+j].value){
                    tempArray[k] = queue[start+i];
                    i++;
                    k++;
                }else{
                    tempArray[k] = queue[start+size1+j];
                    j++;
                    k++;
                }
            }
            while( i < size1 ){
                tempArray[k] = queue[start+i];
                i++;
                k++;
            }
            while( j < size2 ){
                tempArray[k] = queue[start+size1+j];
                j++;
                k++;
            }

            for( i = 0; i < size1+size2; i++){
                queue[start+i] = tempArray[i];
            }
    }
};