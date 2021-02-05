/* 
Trying to create and test sorting algorithms

Lucas de Andrade - 27/01/2021
*/

#include <stdio.h>
#include <time.h>
#include <stdlib.h>

const int SIZE = 10;
const int RANGE = 10;
const int LINESIZE = 10;

void randomize(int *array,int SIZE){
    int i;
    srand(time(0));
    for(i = 0; i<SIZE; i++)
        array[i] = rand() % RANGE;
}

void bubbleSort(int *array,const int SIZE);
void mergeSortManager(int *array, const int SIZE);
void printArray(int *array, const int SIZE,const char *NAME, const short LINESIZE);
void swap(int *a, int *b);
void mergeSort(int *array,int size1, int size2);

int main(){

    // constant to easily change the size of the test array. (Decided to change this into a define statement...)
    // const int SIZE = 10, RANGE = 100, LINESIZE = 10;

    // declaring the array to be tested and the counter for the loops inside main
    int array[SIZE], i;

    // populating the array with random numbers.
    randomize(array,SIZE);

    // Print the randomized array
    printArray(array,SIZE,"Unsorted Array",LINESIZE);

    bubbleSort(array,SIZE);

    // populating the array with random numbers for the second test!

    randomize(array,SIZE);

    printArray(array,SIZE,"Unsorted Array",LINESIZE);

    mergeSortManager(array,SIZE);

    return 0;

}

void bubbleSort(int *array,const int SIZE){

    int i,j,endFlag;
    // int compCounter = 0;

    for( i=0; i<SIZE - 1; i++){
        endFlag = 0;
        for( j = 0; j < SIZE - 1; j++){
            if(array[j] > array[j+1]){
                swap(&array[j],&array[j+1]);
                endFlag++;
            }
            // compCounter++;
        }
        if(i%1000 == 0 || i == SIZE-2)
            printArray(array,SIZE,"Bubbling up",LINESIZE);
        if(!endFlag)
            break;
    }
    //return compCounter;
}

void mergeSort(int *array,int size1, int size2){
// treats 2 sections of an array as 2 separate ordered arrays, and puts all their elements in order back into the original array, starting at the beginning of the first section.
    int i=0,j=0,k=0, tempArray[size1+size2];

    while( i < size1 && j < size2 ){
        if(array[i] < (array+size1)[j]){
            tempArray[k] = array[i];
            i++;
            k++;
        }else{
            tempArray[k] = (array+size1)[j];
            j++;
            k++;
        }
    }
    while( i < size1 ){
        tempArray[k] = array[i];
        i++;
        k++;
    }
    while( j < size2 ){
        tempArray[k] = (array+size1)[j];
        j++;
        k++;
    }

    for( i = 0; i < size1+size2; i++){
        array[i] = tempArray[i];
    }

}

void mergeSortManager(int *array, const int SIZE){

    /* This function is responsible for using the sortmanager correctly to sort a single array.
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

    for ( k = 1; k < SIZE; k*=2 ){
        for( i = 0; i < SIZE; i += 2*k){
            //printf("i: %d, k: %d",i,k);
            if( i + 2*k > SIZE){
                if( SIZE > (i+k) ){
                // printf("\nmergeSort(%p,%d,%d)\n",array+i,k,SIZE-(i+k));
                    mergeSort(array+i,k,SIZE - (i+k));
                }
            }else
            {
                // printf("\nmergeSort(%p,%d,%d)\n",array+i,k,k);
                mergeSort(array+i,k,k);
            }
            
        }
        if( k%256 == 0 || k == SIZE-1)
            printArray(array,SIZE,"Merging !",LINESIZE);
    }

}

void printArray(int *array, const int SIZE,const char *NAME,const short LINESIZE){

    int i;
    printf("\n\n%s\n",NAME);

    for(i = 0; i<SIZE && i < LINESIZE * 3; i++){
        if( i%LINESIZE == 0)
            printf("\n");
                
        printf("%4d  ",array[i]);        
    }
    if( i == LINESIZE * 3){
        printf("\n...");
    }
    printf("\n");
}

void swap(int *a, int *b){
    int temp = *a;
    *a = *b;
    *b = temp;
}