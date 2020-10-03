//
//  main.c
//  FinalProject
//
//  Created by Carly Freedman on 4/23/20.
//  Copyright © 2020 Carly Freedman. All rights reserved.
//


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <wchar.h>
#include "GamePlayFunctions.h"

int main(void) {
    FILE* inp;
    FILE* rules;
    FILE* gameOver;
    srand(time(NULL));
    card *deckHead = NULL;
    int gameMode;
    char key;
    int fileChoice;
    char fileName[100];
    rules = fopen("Rules.txt", "r");
    inp = fopen("Deck.txt", "r");
    
    
    
    PrintRules(rules);
    printf("\nPress 'ENTER' when you are ready to begin.\n");
    key = getchar();
    
    printf("Would you like to:\n\t1. enter the name of your own testing document\n\t2. use a preloaded and shuffled deck?\n");
    scanf("%d", &fileChoice);
    if (fileChoice == 1){
        printf("Enter the name of the file you would like to read from:\n");
        scanf("%s", fileName);
        inp = fopen(fileName, "r");
        MakeDecks(inp, &deckHead);
        fclose(inp);
    }
    else{
        MakeDecks(inp, &deckHead);
        ShuffleDeck(&deckHead);
    }
    printf("Enter the number of the game mode you would like to play in:\n\t1. Classic\n\t2. Party\n");
    scanf("%d", &gameMode);
    
    
    if(gameMode == 1){
        SinglePlayerGame(deckHead, inp);
    }
    else if (gameMode == 2){
        TwoPlayerGame(deckHead, inp);
    }
   
    PrintGameOver(gameOver);
    
    return 0;
}

