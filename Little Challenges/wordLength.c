/* 
Trying to solve an exercise from The C Programming Language by K&R:

Base of this program was made with code examples of the same book.
*/

#include <stdio.h>
#include <stdlib.h>


int main(){

    /* This function counts words, checks the size of the smallest and of the largest words and displays it both as a vertical and horizontal histogram
    */

    const int IN  = 1; // inside a word
    const int OUT = 0; // outside a word 

    int arraySize = 30; // this will decide how long the dynamically sized array wordCount will be;
    int *wordCount;  // this will be used to store a count for each size of word
    int *temp = NULL; // this is just to properly use realloc()
    int c, wc, length; // length will be used to subscript the arrays; wc is just a total word count.
    char state = OUT; // to be used to separate words
    int min = 100, max = 0; // to define the beginning and the end of the histogram
    int i,j; //loop auxiliaries


    if( !( wordCount = (int *) calloc( arraySize,sizeof(int)) ) ){
        printf("\nUnable to allocate memory\n");
        exit(1);
    }

    wc = length = 0;

    printf("\n\nPlease input one line of text.\n\n");

    while( (c = getchar()) != EOF){

        if ( (c >= ' ' && c <= '/') || (c >= ':' && c <= '@') || c == '\t' || c == '\n'){
            /* These characters aren't parts of words!
            if the previous state is IN, it means a word has just ended*/
            if( state == IN ){

                /* A word has ended, the state now becomes OUT.*/    
                state = OUT;
                /* in case the new word is bigger than the current array is made to represent, the array will be reallocated to accomodate this new word!*/
                if( length > arraySize ){
                    
                    if( temp = (int *) realloc(wordCount, length*sizeof(int))){
                        //initialize the new elements of the array to 0
                        for( i = arraySize; i < length; i++)
                            wordCount[i] = 0;
                        // define length as the current arraySize variable for future comparisons.    
                        arraySize = length;
                        
                        wordCount = temp;
                        temp = NULL;
                    }else{
                        free(wordCount);
                        wordCount = NULL;
                        printf("\nUnable to reallocate memory\n");
                        exit(1);
                    }
                }

                /* Now that the array is certainly able to represent the new word
                    we take care of what's needed: increment wordcount, define new minimum size and maximum size of read words, reset the length variable so it can be used again.*/
                ++wordCount[length - 1];
                if( length < min )
                    min = length;
                if( length > max )
                    max = length;
                length = 0;
            }
                /* This program is designed to read a single line from the keyboard, so if a newline character is detected we will break the loop*/ 
            if ( c == '\n' )
                break;
        }else if ( state == OUT ){
            state = IN;
            ++wc;
            ++length;
        }else{
            ++length;
        }
    }

    length = 0;
    for( i = min - 1; i < max; i++)
        if( wordCount[i] > length)
            length = wordCount[i];

    printf("\n\nThere were %d total words."
            "\n\nWord count histogram:\n\n",wc);

    printf("   ");
    for( j = 1; j<=length; j++){
        printf("%3d",j);
    }
    printf("(count)\n   ");
    for( j = length; j>0; j--){
        printf("---");
    }
    printf("\n");

    for( i = min - 1; i < max; i++){

        printf("%2d| ",i+1);
        for( j = wordCount[i]; j > 0; j-- )
            printf("==|");

        printf("\n");
    }
    printf("(size)\n\n");

    printf("Vertical histogram time!\n\n");


    printf("(count)");
    for( j = length; j > 0; --j){
        
        printf("\n%7d|",j);
        for( i = min - 1; i< max; i++){
            if( wordCount[i] >= j)
                printf(" | ");
            else
                printf("   ");
        }
    }
    printf("\n        ");

    for( i = min - 1; i< max; i++)
        printf("---");
    printf("\n        ");
    for( i = min - 1; i< max; i++)
        if( i + 1 < 10)
            printf("%2d ",i+1);
        else
            printf("%3d",i+1);
    printf("\n");
    for( i = min - 1; i< max; i++)
        printf("   ");
    printf("(size)\n\n");

    return 0;
}

