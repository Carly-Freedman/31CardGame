#include <stdio.h>
#include <stdlib.h>

typedef struct card_s{
    struct card_s* prev;
    char suit[9];
    int value;
    char face;
    int direction; 
    struct card_s* next;
}card;

typedef struct graphicCard_s{
    char face[6];
    char suit[6];
}graphicCard;

typedef struct stat_s{
    int numTotal;
    int numPWon;
    int numP14;
    int numDWon;
    int numD27;
}stat;
