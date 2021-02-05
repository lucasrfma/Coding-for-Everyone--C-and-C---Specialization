#include <stdio.h>

void average(int array[]);

int main(){

	int a = 1;
	int array[5];
	int* p = &a, *p2array = array;
	char b = '1',*pt = &b;
	//char* pt = &b;
	 

	printf("\n\nThe size of int[5] is %d",sizeof array);
	printf("\n\nThe size of p2array is %d",sizeof p2array);
	average(array);


	// printf("\n\nThe size of int* is %d",sizeof p);
	// printf("\n\nThe size of char* is %d",sizeof pt);

	// printf("\n\nThe Value of a is %d",a);
	// printf("\n\nThe Value of p is %d",p);
	// printf("\n\nThe Address of a is %d",&a);
	// printf("\n\nThe Value stored in the address pointed by p is %d",*p);

	// *p = 256;

	// printf("\n\nThe Value of a is %d",a);
	// printf("\n\nThe Value of p is %lld",p);
	// printf("\n\nThe Address of a is %lld",&a);
	// printf("\n\nThe Value stored in the address pointed by p is %d",*p);

	// printf("\n\nThe Value of b is %d",b);
	// printf("\n\nThe Value of pt is %lld",pt);
	// printf("\n\nThe Address of b is %lld",&b);
	// printf("\n\nThe Value stored in the address pointed by pt is %d",*pt);

	// printf("\n\nThe address of array is %llu, and the address of array + 1 is %llu",array, array+1);

	// printf("\n\nThe address of array is %llu, and the address pointed by p2array + 1 is %llu",p2array, p2array+1);
	return 0;
}

void average(int array[]){

	printf("\n\nThe size of int[5] is %d",sizeof array);
	
}