/*
Coursera - University of California, Santa Cruz - C for Everyone

Peer-graded Assignment: Compute the average weight for a population of elephant seals read into an array

In this peer reviewed assignment, you will use an array to calculate an average from raw data—specifically the average weight of the northern elephant seal (Mirounga angustirostris).
You will submit a file with your program for your fellow learners to review, and you will review three of your fellow learners' programs. 
*/

#include <stdio.h>
#include <stdlib.h>

char *readNumber(FILE *input, int maxSize);

int main(){

    FILE *fp;
    // char fileName[] = "elephant_seal_data.txt"; // defines the file to be read
    char fileName[] = "sampleAvg.txt"; // test file with few and small numbers


    char *nextNumber; // this is just for use with strtod(). Since I will be using strtod() in conjunction with the readNumber() function I created below, this will not be used.
    double value = 0.0, average = 0.0;
    int i = 1;

    if( !(fp = fopen(fileName,"r")) ){
        printf("\n\nCould not open file %s.\nPlease check if the name is correct and if it is in the same directory as the program!\n",fileName);
        return 1;
    }
    printf("\ntest 1.");

    while ( value = strtod( readNumber(fp, 100), &nextNumber ) ){ //this works without any extra steps because I know the source file doesn't have any numbers equal to 0, since its a list of animal weights
        printf("\ntest 1.");
        average += (value - average)/i++;                         // here I used the average algorithm from the "discussion prompt" in week 2 of the course.
    }




    return 0;

}

char *readNumber(FILE *input, int maxSize){

    /* This function finds the next string section that represents a number and returns it
        It has 2 parameters: FILE *input to receive a pointer to a file (should work with stdin too...)
        and int maxSize, that will define the longest array of characters representing a number to be read.
        
        As the function reallocates the array to the smallest it needs be at the end, I don't think it should be a problem to oversize
        the maxSize parameter when calling this.*/

    char *number = (char *) malloc(maxSize); // allocates a string array with the maximum size received as the second parameter.
    char *resized = NULL; // to be used for error handling purposes when calling realloc later.

    const char IN = 1;  // Defines 2 constants: IN and OUT to help control the state
    const char OUT = 0;
    char state = OUT;   // The state is used to now if a non-digit character is from before or after a number was read.

    int c, digits = 0;  // digits will be used to record how many digits were encountered

    while( (c = getc(input)) != EOF){
        
        if ( c >= '0' && c <= '9' ){
            state = IN;             // c was recognized as a digit, so it will be assined to the array subscribed by the number of previously read digits
            number[digits++] = c;   // digits is then incremented. 
        }
        else if( state == IN ){     // c was recognized as a non-digit AFTER at least 1 digit was already found.
            if ( c == '.' )         // if it's a dot, it will be then treated as part of the number
                number[digits++] = c;
            else{                   // if it isn't a dot, it's not part of a number, so we conclude the loop
                break;
            }
        }                            
    }
    number[digits++] = '\0';    // after the loop we mark the end of the string. This is done outside the loop so it happens even if EOF is found.

    if( (resized = (char *) realloc(number, digits)) != NULL ){
        number = resized;
    }else{
        printf("\nMemory block trimming failed!\n");
    }

    return number;
}