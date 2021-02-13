/*
C for Everyone: Structured Programming Week 3 Honors assignment:

1 - Modify singly linked list into doubly linked list;
2 - Create a list of 200 random elements from 0 to 49;
3 - Remove duplicate elements:
    -> a ) Sort the list and remove consecutive equal elements;
       b ) Take each element in order and compare them to the rest of the list, removing duplicates.

I had changed the list trying to make it more like an OO class, so I kept the changes here, but most of it is really similar to the list as seen in the lecture videos.
I chose option "sort then remove" because I think it makes it easier to check for leftover duplicates at the end and see that it really is working.

Lucas Romero da F. M. de Andrade
feb. 13 2021

*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// size of the randomized list
#define SIZE 200
// range of the random values
#define RANGE 50
// number of element in each line
#define LINESIZE 5

typedef struct doubleLinkListElement{
    int data;
    struct doubleLinkListElement *next;
    struct doubleLinkListElement *previous;
}doubleLinkListElement;

typedef struct doubleLinkList{
    doubleLinkListElement* head;
    doubleLinkListElement* cursor;
    int size;
}doubleLinkList;

void setCursorPosition(doubleLinkList *lst, int position){

    /* Sets cursor to the position received as an argument*/

    int i;

    lst->cursor = lst->head;

    for( i = 0; i < position; ++i){
        lst->cursor = lst->cursor->next;
    }
}

void printList(doubleLinkList *lst, int lineSize){
    // prints a list starting from the element pointed by the cursor
    // It will divided in lines of lineSize elements.
    int i = 0;

    while (lst->cursor){
        if( i % lineSize == 0){         // every lineSize elements, a \n is inserted
            printf("\n%3d|  %2d",i/lineSize,lst->cursor->data);  
        }else{
            printf(" : %2d",lst->cursor->data); // the separation between members of the same line is printed before each element from the second
        }
        lst->cursor = lst->cursor->next;
        ++i;
    }
}

void prepend(doubleLinkList *lst, int dt){
    
    /* Creates a new element and sets it to be the new head, links it to the previous head.*/

    // allocates the new element.
    doubleLinkListElement *newHead =  (doubleLinkListElement *) malloc(sizeof(doubleLinkListElement));

    // Since the last head will be linked, we need to know if it exists.
    if( lst->head == NULL){
        newHead->next = NULL;
    }else{
        lst->head->previous = newHead;
        newHead->next = lst->head;
    }
    
    // printf("\n\npos. 2 | data: %d\n\n",dt);
    newHead->data = dt;
    newHead->previous = NULL;

    // set both the head and the cursor to the new element.
    lst->cursor = lst->head = newHead;
    // increments list size
    lst->size++; 
}

void freeList(doubleLinkList *lst){

    // frees the whole list
    doubleLinkListElement *temp;
    if(lst->head){
        while( lst->head->next ){
            // saves the current element, starting at the first
            temp = lst->head;
            // saves the position of the next element
            lst->head = lst->head->next;
            // frees the current element
            free(temp);
        }
    }

    lst->head = lst->cursor = NULL;
    lst->size = 0;
}

void arrayToList(doubleLinkList *lst, int array[],int size){

    // receives a null doublelinkList and copies the received array into it
    int i;
    
    if(lst->head != NULL){
        printf("\n\nTrying to copy an array to a list with pre-existing elements.");
        exit(1);
    }

    // this is a modified version of the function shown in the lecture made so the list doesn't have the array elements reversed.

    for(i = size-1; i >=0; --i){
        prepend(lst,array[i]);
    }

}

void swapElements(doubleLinkListElement *lst1, doubleLinkListElement *lst2){
    // simple swap function that swaps the data of two list elements.
    int temp;

    temp = lst1->data;
    lst1->data = lst2->data;
    lst2->data = temp;
}

void removeElement(doubleLinkList *lst){

    /* Removes the element pointed by the cursor from the list
       The cursor is moved to the element before the removed element */
    doubleLinkListElement *temp;

    // save current node's address on temporary variable
    temp = lst->cursor;

    // links the previous node to the next node
    lst->cursor->previous->next = lst->cursor->next;
    if(lst->cursor->next != NULL){
        lst->cursor->next->previous = lst->cursor->previous;
        // moves cursor to next node (which will be in this one's position)
        lst->cursor = lst->cursor->next;
    }else{
        lst->cursor = lst->head;
    }

    // decrements list size
    lst->size--;

    // free the removed node
    free(temp);
}

void bubbleSort(doubleLinkList *lst){

    int i,j,endFlag;

    for( i=0; i < lst->size - 1; ++i){
        lst->cursor = lst->head; // we need cursor to point at the head of the list at each start of outer loop iteration
        endFlag = 0;
        // this inner loop goes through the whole list comparing one element with the next
        // each iteration of the outer loop guarantees the last item is in place, so the size of the inner loops decrements accordingly
        for( j = 0; j < lst->size - (i+1); ++j){
            if( lst->cursor->data > lst->cursor->next->data ){
                swapElements(lst->cursor,lst->cursor->next);
                endFlag++; // this counts the number of swaps in an outer loop iteration. 
            }
            lst->cursor = lst->cursor->next;  //at the end of the comparison, we move to the next element, until we get to the last and the loop breaks
        }
        if(!endFlag) // An iteration with 0 swaps means the function can end early.
            break;
    }
}

doubleLinkList* newList(){
    
    doubleLinkList *list;

    list = (doubleLinkList*) malloc(sizeof(doubleLinkList));
    list->head = NULL;
    list->cursor = NULL;
    list->size = 0;

    return list;

}

void removeSequentialDuplicates(doubleLinkList *lst){
    /* Removes sequential duplicates.
        It will compare each node to the previous one, starting from the second node
        and remove it if they have the same data. */

    int i, previousSize = lst->size;
    setCursorPosition(lst,1); // starts at the second node

    for( i = 1; i < previousSize; ++i){
        if( lst->cursor->data == lst->cursor->previous->data ){
            removeElement(lst);
        }else{
            lst->cursor = lst->cursor->next; // this is inside the else because the removeElement() function already moves the curser to the next element.
        }    
    }
    
}

int main(){

    doubleLinkList *list = newList();
    int i, array[SIZE];

    // create a randomized array of 100 integers
    srand(time(NULL));

    for( i = 0; i < SIZE; ++i){
        array[i] = rand() % RANGE;
    }

    // creates a list from the array
    arrayToList(list,array,SIZE);

    // Prints unsorted list
    printf("\n\nUnsorted List: \n");
    printf("%d elements:\n",list->size);
    printList(list,LINESIZE);
    
    // sort the list
    bubbleSort(list);

    // resets cursor position
    setCursorPosition(list,0);
    // prints the sorted list
    printf("\n\nSorted List: \n");
    printf("%d elements:\n",list->size);
    printList(list,LINESIZE);
    

    // removes sequential duplicates.
    removeSequentialDuplicates(list);

    // resets cursor position
    setCursorPosition(list,0);
    
    // prints the trimmed list
    printf("\n\nTrimmed List: \n");
    printf("%d elements:\n",list->size);
    printList(list,LINESIZE);
    printf("\n\n");


    // frees every element of the list
    freeList(list);
    // frees the list itself.
    free(list);

    return 0;
}