#include <stdio.h>

typedef struct{
    int pips;
    //char* suit;
    enum suit{
        CLUBS = 'C', 
        SPADES = 'S', 
        HEARTS = 'H', 
        DIAMONDS = 'D'
        }suit;
}card;

struct test{
    int pips;
    char* suit;
};

char *clubs = "clubs";
char *spades = "spades";
char *hearts = "hearts";
char *diamonds = "diamonds";

struct point{
double x;
double y;
} p1 = {4};

int main(){

    // card deck[52];
    // struct test testD[52];


    card first = {12, CLUBS};

    struct test second = {11, hearts};

    card third;

    card fourth, *pointer_2_4;

    pointer_2_4 = &fourth;

    pointer_2_4->pips = 13;
    pointer_2_4->suit = SPADES;


    third.pips = 10;
    third.suit = DIAMONDS;

    printf("\n\nYou drew the card %d of %c",first.pips,first.suit);
    printf("\n\nYou drew the card %d of %s",second.pips,second.suit);
    printf("\n\nYou drew the card %d of %c",third.pips,third.suit);\
    printf("\n\nYou drew the card %d of %c",pointer_2_4->pips,fourth.suit);

    printf("\n\nValue is: %lf  %lf",p1.x,p1.y);

    return 0;
}