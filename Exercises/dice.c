#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIDES 6
#define ROLL (rand() % SIDES)

void histogramV(int data[], int length,char *ylabel,char *xlabel, int yUnit);

int main(){

    int i,throws,results[SIDES] = {0},yaxis;
    srand(clock());

    printf("Insert the number of rolled dice: ");
    scanf("%d",&throws);
    printf("Insert the granularity of the y axis: ");
    scanf("%d",&yaxis);

    for( i = 0; i < throws; i++){
        results[ROLL]++;
    }

    histogramV(results,SIDES,"count","results",yaxis);

    return 0;

}

void histogramV(int data[], int length,char *ylabel,char *xlabel, int yUnit){

    int i,j,max = 0;

    for( i = 0; i<length; i++)
        if( max < data[i] )
            max = data[i];


    printf("(%s)",ylabel);
    
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

    for( i = 0; i< length; i++)
        printf("---");

    printf("\n        ");
    for( i = 0; i< length; i++)
        if( i + 1 < 10)
            printf("%2d ",i+1);
        else
            printf("%3d",i+1);

    printf("\n");
    for( i = 0; i< length; i++)
        printf("   ");
    printf("(%s)\n\n",xlabel);

}