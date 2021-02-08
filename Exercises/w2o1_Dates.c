/*
C for Everyone: Structured Program Week 2
Option 1 (General)
Write enumerated types that supports dates—such as december 12. Then add a function that produces a next day.  
So nextday(date) of december 12 is december 13. Also write a function printdate(date) that prints a date legibly.
The function can assume that February has 28 days and it most know how many days are in each month. 
Use a struct with two members; one is the month and the second  is the day of the month—an int (or short).

Lucas Romero de Andrade - 04/02/2021
*/

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

typedef enum{jan, feb, mar, apr, may, jun, jul, aug, sep, oct, nov, dec}month; // enum required by the assignment
const short daysMonth[] = {31,28,31,30,31,30,31,31,30,31,30,31}; // a constant vector so that the program knows the last day of each month
const char *MONTH_NAME[] = {"january","february","march","april","may","june","july","august","september","october","november","december"};
// this will be used when printing the date, such as "december 12" in the description of the task.

typedef struct date{ // struct as required
    month m;
    short d;
}date;

date nextday(date dt){

    dt.m %= 12;                               // Turns an invalid month into a valid month
    dt.d = ( (dt.d-1) % daysMonth[dt.m]) + 1; // Turns an invalid day into a valid day

    if( dt.d == daysMonth[dt.m]){ // the day after the last day of the month is the first day of the next month
        dt.d = 1;
        dt.m = (dt.m + 1)%12;
    }else{
        dt.d++;
    }

    return dt;
}

void printdate(date dt){
    dt.m %= 12;                               // Turns an invalid month into a valid month
    dt.d = ( (dt.d-1) % daysMonth[dt.m]) + 1; // Turns an invalid day into a valid day
    printf("%s %d", MONTH_NAME[dt.m],dt.d);
}

int main(){

    date dt = {jan, 1};

    printf("\n\nThe first day is: ");
    printdate(dt);

    while( dt.m != mar){   // change this to test the nextday() function
        dt = nextday(dt);

        printf("\nAnd the next is:  ");
        printdate(dt);
    }

    return 0;
}