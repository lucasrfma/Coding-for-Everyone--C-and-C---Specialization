#include <stdio.h>

#define MAX 100
#define EMPTY -1
#define FULL (MAX - 1)

typedef struct{
    char vl[MAX];
    int top;
}stack;

void reset( stack *stk){
    stk->top = EMPTY;
}

char is_empty(const stack *stk){
    return stk->top == EMPTY;
}

char is_full(const stack *stk){
    return stk->top == FULL;
}

void push( int value, stack *stk){
    if( !is_full(stk) )
        stk->vl[++stk->top] = value;
}

char pop(stack *stk){
    return stk->vl[stk->top--];
}

char top(const stack *stk){
    return stk->vl[stk->top];
}


int main(){

    char sentence[] = "This is a test!";
    stack stk;
    int i;
    
    printf("\n\n%s\n",sentence,sizeof sentence);

    for( i = 0; i < sizeof sentence && sentence[i] != '\0'; i++){
        push(sentence[i], &stk);
    }

    for( i = 0; i < sizeof sentence && sentence[i] != '\0'; i++){
        sentence[i] = pop(&stk);
        printf("\n%s",sentence,sizeof sentence);
    }

    printf("\n\n%s",sentence,sizeof sentence);


    return 0;
}