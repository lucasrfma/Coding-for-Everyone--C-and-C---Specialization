/*Calculate the average value*/

#include<stdio.h>
#include<math.h>

int main(void)
{    
    
    int arr_size;   	//define array range variable
    printf("Enter how many elephant's weight you enter:");
    scanf("%d",&arr_size);  //get array size
    printf("%d",arr_size);


    int arr_weight[arr_size];   //declare a array
    int i=0;

    while(i<arr_size){
        printf("Enter elephant weight:");
        scanf("%d",&arr_weight[i]);     //add values to the array
        i++;
    }


    int sum=0,count=0;		//define variables to calculate the average
    i=0;
    

    while(i<arr_size){			//get the sumation of the inputs array rangr
        sum=sum+arr_weight[i];      //calculate the total weight
        count++;
        i++;
    }
    double avg;
    avg=sum/count;  //calculate the average value
    printf("%lf",avg);	//return the average value
   
   }   