#include <stdio.h>

/*
This is just a standalone function I created, originally, as a part of the wordLength.c file.
That file was my try at an exercise from K&R The C Programming Language book. Displaying the result as a histogram was also a suggestion by that book

Arguments:
int data[] :  well, the data
length :      length of the data
ylabel and xlabel: the labels for the coordinates
yUnit : defines the rate of the decrement used in the drawing part, so the histogram is shorter the bigger this number is.
*/

int histogramV(int data[], int length,char *ylabel,char *xlabel, int yUnit){

    
    int i,j,max = 0;

    // yUnit needs be positive!
    if( yUnit <= 0)
        yUnit = 1;

    // finding out what the max is so we know where to start. The drawing is top-to-bottom
    for( i = 0; i<length; i++)
        if( max < data[i] )
            max = data[i];


    printf("(%s)",ylabel);
    
    //this draws the body of the histogram, with the vertical units and the bars for each array element that is at least that big.
    for( j = max; j > 0; j = j - yUnit){
        
        printf("\n%7d|",j);
        for( i = 0; i< length; i++){
            if( data[i] >= j)
                printf(" | ");
            else
                printf("   ");
        }
    }
    printf("\n        ");
    // just a horizontal bar to separate the graph from the X axis' values
    for( i = 0; i< length; i++)
        printf("---");
    // drawing the X axis' values
    printf("\n        ");
    for( i = 0; i< length; i++)
        if( i + 1 < 10)
            printf("%2d ",i+1);
        else
            printf("%3d",i+1);
    // just to put the xlabel at the correct location
    printf("\n");
    for( i = 0; i< length; i++)
        printf("   ");
    printf("(%s)\n\n",xlabel);

}
