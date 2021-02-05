#include <stdio.h>

int fibonaciIterative(int n);
int fibonaciRecursive(int n);

int main(){

    int n, i;

    printf("\n\nFibonaci calculator!!\n\nUp to what number do you want to see?\nn: ");
    scanf("%d",&n);

    printf("\nThis is the iterative fibonaci table from 0 to %d\n",n);
    for( i = 0; i <= n; i++)
        printf("\nThe fibonaci value of %d is %d",i,fibonaciIterative(i));

    printf("\n\nThis is the recursive fibonaci table from 0 to %d\n",n);
    for( i = 0; i <= n; i++)
        printf("\nThe fibonaci value of %d is %d",i,fibonaciRecursive(i));

	return 0;
}

int fibonaciIterative(int n){

    int fibo = 1,i=2, prev1 = 0,prev2;

    if( n < 2 ){
        if( n == 0)
            return 0;
        else if( n == 1)
            return 1;
        else {
            printf("\n\nInvalid number\n\n");
            return 0;
        }
    }
    
    for(; i<= n; i++){

        prev2 = prev1;
        prev1 = fibo;
        fibo = prev1 + prev2;

    }

    return fibo;

}
int fibonaciRecursive(int n){

    if( n < 2 ){
        if( n == 0)
            return 0;
        else if( n == 1)
            return 1;
        else {
            printf("\n\nInvalid number\n\n");
            return 0;
        }
    }

    return fibonaciRecursive(n-1)+fibonaciRecursive(n-2);

}