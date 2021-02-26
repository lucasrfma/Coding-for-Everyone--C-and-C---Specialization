/*
C for Everyone: Structured Programming Week 3 assignment:
"Option 1 (General) 
Use the linear linked list code to store a randomly generated set of 100 integers.  
Now write a routine that will rearrange the list in sorted order of these values. Note you might want to use bubble sort to do this. Print these values in rows of 5 on the screen.

How will this work? Compare two adjacent list elements and if they are out of order swap them. After a first pass the largest element will have bubbled to the end of the list. 
Each pass can look at one less element as the end of a list stays sorted."

Lucas Romero da F M de Andrade
feb. 11 2021
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// size of the randomized list
#define SIZE 100
// range of the random values
#define RANGE 100
// number of element in each line
#define LINESIZE 5

typedef struct list{
    int data;
    struct list *next;
}list;

void printList(const list *lst, int lineSize){
    // Modified the function presented in the lecture to attend to the 5 elements per line requisite of this assignment
    int i = 0;
    while (lst){
        if( i % lineSize == 0){         // every lineSize elements, a \n is inserted
            printf("\n%2d",lst->data);  
        }else{
            printf(" : %2d",lst->data); // the separation between members of the same line is printed before each element from the second
        }
        lst = lst->next;
        ++i;
    }
}

list* addToFront(list *lst, int dt){
    // function to create a new list item/element, but this time adds it to the front
    // it returns the address of the item created, so it should be called something like:
    // head = addToFront(head);

    list *head = (list*) malloc(sizeof(list));
    head->data = dt;
    head->next = lst;

    return head;

}

list* freeList(list **lst){

    // frees the list starting at the received element.

    list *temp;
    if(*lst){
        while( (*lst)->next ){
            temp = (*lst);
            *lst = (*lst)->next;
            free(temp);
        }
        free(*lst);
    }

    return NULL;
}

list* arrayToList(int array[],int size){

    // this is a modified version of the function shown in the lecture made so the list doesn't have the array elements reversed.
    list *head = NULL;
    int i;

    for(i = size-1; i >=0; --i){
        head = addToFront(head,array[i]);
    }
    return head;
}

void swapElements(list *lst1, list *lst2){
    // simple swap function that swaps the data of two list elements.
    int temp;

    temp = lst1->data;
    lst1->data = lst2->data;
    lst2->data = temp;
}

void bubbleSort(list *lst,const int size){

    int i,j,endFlag;
    list *start = lst;

    for( i=0; i<SIZE - 1; ++i){
        endFlag = 0;
        // this inner loop goes through the whole list comparing one element with the next
        for( j = 0; j < SIZE - 1; ++j){
            if( lst->data > lst->next->data){
                swapElements(lst,lst->next);
                endFlag++; // this counts the number of swaps in an outer loop iteration. 
            }
            lst = lst->next;  //at the end of the comparison, we move to the next element, until we get to the last and the loop breaks
        }
        if(!endFlag) // An iteration with 0 swaps means the function can end early.
            break;
        lst = start; // each time we end the outer loop (bubble the biggest element up to the end of the list) we need to go back to the start.
    }
}

int main(){

    list *head = NULL;
    int i, array[SIZE];

    // create a randomized array of 100 integers
    srand(time(NULL));

    for( i = 0; i < SIZE; ++i){
        array[i] = rand() % RANGE;
    }

    // printf("\nTesting from array now:\nOriginal array:\n");

    // for (i = 0; i < SIZE; i++){
    //     printf("%d  ",array[i]);
    // }
    
    // creates a list from the array
    head = arrayToList(array,SIZE);
    // Prints unsorted list
    printf("\nUnsorted List: \n");
    printList(head,LINESIZE);

    // sort the list
    bubbleSort(head,SIZE);
    
    // prints the sorted list
    printf("\n\nSorted List: \n");
    printList(head,LINESIZE);
    printf("\n\n");
    // frees every element of the list
    head = freeList(&head);

    return 0;
}