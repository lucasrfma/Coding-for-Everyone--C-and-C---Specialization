/*
    Testing some ways to operate input and output in the C language
*/

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

int readLine(char** line, const int SIZE);

int main(){

    int c, bufferSize = 256;
    char *input;
    
    printf("\n\nThis is an input/output test!\n\n");

    c = readLine(&input,bufferSize);
    
    printf("\n\nThe line read was: \n\"%s\""
            "\nThe size of the line was %d"
            "\n%d characters was thrown away due to buffer overflow.",input,_msize(input)+c,c);


    return 0;

}

int readLine(char** line, const int SIZE){

    /* This function is used to take input from the user, allocate a suitably sized string to represent it.
        Workings:
        
        Receives the address of a character pointer (a "string" variable);
        It allocates a character array with the size specified on the second argument and populates it with characters from stdin, and assigns the address of this array to the pointer received as an argument.

        It throws away characters exceeding the size of the initial array.

        In case the input is smaller than that size, the array is reallocated to save memory.

        The program returns an integer value that can either be an error code or the number of overflowed characters.
        */

    int i = 0;              // loop control counter
    int overflow = 0;
    int c;
    char *resized;
    
    // line is a pointer of a pointer. It needs be so the original pointer that was passes by reference from a calling function can be changed
    if(!(*line = (char *) malloc(SIZE))){ // This means we will put the address of the newly allocated memory stack in the content of line.
        printf("\nMemory allocation when reading a line failed.\n");
        return -1;
    }

    while( (c = getchar()) != EOF ){    // Reads characters until EOF is found.

        (*line)[i] = (char) c;          // Puts character into char array
        if( (*line)[i] == '\n' )        // Checks if the newest character read is a new line character
            break;                      // If it is, the loop is broken

        i++;                            // char array index of next character is incremented
        if( i == SIZE){                 // Checks for buffer overflow. If there is overflow:
            overflow++;                 // 1 - flags the overflow
            i--;                        // 2 - decrements the array index to go back into the range of the array
            break;                      // 3 - breaks the loop.
        }
    } 


    (*line)[i] = '\0';      // Here we transform the current character array into a proper string.

    if(overflow){   // here we check if there was overflow. 
        for( ; (c = getchar()) != EOF && c != '\n'; overflow++);   // This loop throws away the exceeding input and counts the exceeding characters.
    }else           // if there wasn't overflow, the current amount of allocated memory is probably bigger than the string size
    {
        if(resized = (char *) realloc(*line, i+1)){
            *line = resized;
        }else{
            printf("\nMemory block trimming failed!\n");
            return -2;
        }
    }
    

    return overflow;
}