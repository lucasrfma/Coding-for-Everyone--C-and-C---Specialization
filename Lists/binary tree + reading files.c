/*  C for Everyone: Structured Programming - Honors Peer-graded Assignment: Week 4 Honors Assignment
    Open and read a file of integer pairs into an array that is created with the first integer telling you how many to read.  
    So  4 9  11  4  5    would mean create an integer array size 4 and read into data[].   
    Write a routine that places these values into a binary tree structure. Then walk the tree “inorder” and print these values to the screen.
    Submit your work in a text file.

    Please, create a file such as described in the instructions above and use its name as a parameter when calling this program.
    I have simply used the binaryTree as presented in the videos before and added them to the week 4 mandatory assignment.

    Lucas Romero da F M de Andrade
    feb. 22 2021
*/

#include <stdio.h>
#include <stdlib.h>

typedef int DATA;

typedef struct node{
    DATA data;
    struct node *left;
    struct node *right;
}NODE;

typedef NODE *BTREE;

void inorder(BTREE root){
    /* Recursive function to print a binary tree starting from the leftmost node all the way to the rightmost node
       Same as presented in the video lecture.*/
    if ( root != NULL){
        inorder( root -> left );
        printf("%d ", root->data);
        inorder( root -> right );
    }
}

BTREE new_node(void){
    return ( (BTREE) malloc(sizeof(NODE)) );
}

BTREE init_node(DATA dt, BTREE bt1, BTREE bt2){
    BTREE bt;
    bt = new_node();
    bt -> data = dt;
    bt -> left = bt1;
    bt -> right = bt2;
    return bt;
}

BTREE create_tree(DATA a[], int i, int size){
    /* int i represents the current element of the array to be put in a node
        size is the size of the whole array*/
    // when the recursion passes the last element of the array, it returns NULL;
    if( i >= size){
        return NULL;
    }else{
        return( init_node( a[i], // create current node with the current element of the array ( i )
                                create_tree(a,2*i+1, size),     // calls for the creation of the left node, passing the index i*2+1
                                create_tree(a,2*i+2, size) ));  // calls for the creation of the left node, passing the index i*2+2
    }
    
}
 
int createArray(FILE *ifp, int **array){
    // allocates an int array the size indicated by the first in in the file pointed by ifp
    // returns the size
    
    int size;

    rewind(ifp);

    if( fscanf(ifp,"%d",&size) == 0 ){
        printf("Error reading the first integer.");
        exit(1);
    }

    // printf("%d",size);
    *array = (int *)malloc(size*sizeof(int));

    return size;
    
}

void readInts(FILE *ifp,int array[],int *size){
    // this function reads ints from the file pointer by ifp
    // it reads every int it can, up to the number pointed by size
    // at the end it updates size, in case there weren't as many ints read from the file as there should be
    int i;
    for( i = 0; i < *size && (fscanf(ifp,"%d",array+i) == 1); ++i);
    *size = i;
}


int main(int argc, char *argv[]){
// int main(void){

    FILE *ifp;
    BTREE tree;
    int *data;
    int size, i;
    double average = 0.0;
    int max;

    // checks for proper amount of arguments
    if( argc != 2){
        printf("\n\nThere needs to be two arguments: executable and inputfile.\n");
        exit(1);
    }

    // open files
    ifp = fopen(argv[1],"r");
    // ifp = fopen("input.txt","r");

    // creates an array with the size defined in the first integer in the file
    size = createArray(ifp,&data);
    // fills the array with the other integers in the file
    readInts(ifp,data,&size);

    // calculates average, as well as identifies their max.
    for( i = 0; i < size; ++i){
        average += ((double) data[i] - average)/(i+1);
        if( i == 0 || data[i] > max){
            max = data[i];
        }
    }

    tree = create_tree(data, 0, size);
    inorder(tree);

    return 0;
}