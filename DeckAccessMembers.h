//
//  DeckAccessMembers.h
//  FinalProject
//
//  Created by Carly Freedman on 5/2/20.
//  Copyright © 2020 Carly Freedman. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <wchar.h>
#include "TypeDefinitions.h"

//Getters:
int countCards(card** hp);
void PrintDeck(card** hp);
int HandSum(card** hp);

//Setters
void MakeDecks(FILE* inp, card** deckHead);
void LoadDeck(card** head, int tempValue, char tempSuit, char tempFace);
void ShuffleDeck(card** head);
void FreeDeck(card** hp);



int countCards(card** hp){
    int count = 0;
    card* temp;
    temp = *hp;
    while (temp != NULL){
        count++;
        temp = temp->next;
    }
    return count;
}


void PrintDeck(card** hp){
    int numCards = countCards(hp);
    card* listp = *hp;
    graphicCard temp[numCards];
    
    
    int i = 0;
    while ( listp != NULL){
        
        if((listp->face == '\0' && listp->value != 10)){
            temp[i].face[0] = ' ';
            temp[i].face[1] = listp->value + 48;
            temp[i].face[2] = '\0';
        }
        else if(listp->value == 10 && listp->face == '\0'){
            temp[i].face[0] = 49;
            temp[i].face[1] = 48;
            temp[i].face[2] = '\0';
        }
        else{
            temp[i].face[0] = ' ';
            temp[i].face[1] = listp->face;
            temp[i].face[2] = '\0';
        }
        
        if (listp->direction == 1){
            strcpy(temp[i].face, " \u2588");
        }
        
        if(listp->suit[0] == 'd'){
            strcpy(temp[i].suit, "\u2666");
        }

        else if(listp->suit[0] == 'h'){
            strcpy(temp[i].suit, "♥");
        }

        else if(listp->suit[0] == 's'){
            strcpy(temp[i].suit, "\u2660");
            
        }

        else if(listp->suit[0] == 'c'){
            strcpy(temp[i].suit, "\u2663");
        }
        
      
        i++;
        listp = listp->next;
    }
    
    
     for(i = numCards - 1; i >= 0; i--){
        if(i == numCards - 1){
            printf(" _________");
        }
        else{
            printf("______");
        }
    }
    printf("\n");
    
     for(i = numCards - 1; i >= 0; i--){
        if(i == numCards - 1){
            printf("|%s     %s|", temp[i].face, temp[i].face);
        }
        else{
            printf("   %s|", temp[i].face);
        }
    }
    
    printf("\n");
    
    for(i = numCards - 1; i >= 0; i--){
        if(i == numCards - 1){
            printf("| %s     %s |", temp[i].suit, temp[i].suit);
        }
        else{
            printf("   %s |", temp[i].suit);
        }
    }
    
    printf("\n");
    
    for(i = numCards - 1; i >= 0; i--){
        if(i == numCards - 1){
            printf("|         |");
        }
        else{
            printf("     |");
        }
    }
    
    printf("\n");
    
     for(i = numCards - 1; i >= 0; i--){
        if(i == numCards - 1){
            printf("|    %s    |", temp[i].suit);
        }
        else{
            printf("     |");
        }
    }
    
    printf("\n");
    
    for(i = numCards - 1; i >= 0; i--){
        if (i == numCards - 1){
            printf("|         |");
        }
        else{printf("     |");
        }
    }
    
    printf("\n");
    
    for(i = numCards - 1; i >= 0; i--){
        if(i == numCards - 1){
            printf("| %s     %s |", temp[i].suit, temp[i].suit);
        }
        else{
            printf("    %s|", temp[i].suit);
        }
    }
    
    printf("\n");
    
    for(i = numCards - 1; i >= 0; i--){
         if(i == numCards - 1){
             printf("|%s     %s|", temp[i].face, temp[i].face);
         }
         else{
             printf("   %s|", temp[i].face);
         }
    }
    
    printf("\n");
    
     for(i = numCards - 1; i >= 0; i--){
        if(i == numCards - 1){
            printf(" ---------");
        }
        else{
            printf("------");
        }
    }
    printf("\n");
    
    
    listp = *hp;
    while(listp != NULL){
        if(listp->direction == 1){
            listp->direction = 0;
        }
        listp = listp->next;
    }
    
}


int HandSum(card** hp){
    int sum = 0;
    card* temp = *hp;
    while(temp != NULL){
        sum += temp->value;
        temp = temp->next;
    }
    return sum;
}


void MakeDecks(FILE* inp, card** deckHead){
    int tempValue;
    char tempSuit;
    char tempFace;
    while(fscanf(inp, "%d %c", &tempValue, &tempSuit) != EOF){
        if (tempValue == 1){
            tempFace = 'A';
        }
        else if (tempValue == 11){
            tempFace = 'J';
            tempValue = 10;
        }
        else if (tempValue == 12){
            tempFace = 'Q';
            tempValue = 10;
        }
        else if (tempValue == 13){
            tempFace = 'K';
            tempValue = 10;
        }
        else{
            tempFace = '\0';
        }
        LoadDeck(deckHead, tempValue, tempSuit, tempFace);
    }
    return;
}

void LoadDeck(card** head, int tempValue, char tempSuit, char tempFace){
    card* newCard = (card*)malloc(sizeof(card));
    card* lastCard = *head;
    newCard->value = tempValue;
    newCard->suit[0] = tempSuit;
    newCard->face = tempFace;
    newCard->direction = 0;
    newCard->next = NULL;
        
        if(*head == NULL){
            newCard->prev = NULL;
            *head = newCard;
            return;
        }
        
        else{
            while(lastCard->next != NULL){
                lastCard = lastCard->next;
            }
            
            lastCard->next = newCard;
            newCard->prev = lastCard;
            }
    return;
}



void ShuffleDeck(card** head){
    card* temp1 = (card*)malloc(sizeof(card));
    card* temp2 = (card*)malloc(sizeof(card));
    card* temp3 = (card*)malloc(sizeof(card));
    int random1, random2;
    int numCards = countCards(head);
    int i, j;
    for(j = 0; j <= 100000; j++){
        temp1 = *head;
        temp2 = *head;
        random1 = rand() % numCards;
        random2 = rand() % numCards;
        for( i = 0; i < random1; i++){
            temp1 = temp1->next;
        }
        for(i = 0; i < random2; i++){
            temp2 = temp2->next;
        }
        temp3->value = temp1->value;
        temp3->suit[0] = temp1->suit[0];
        temp3->face = temp1->face;
        temp1->value = temp2->value;
        temp1->suit[0] = temp2->suit[0];
        temp1->face = temp2->face;
        temp2->value = temp3->value;
        temp2->suit[0] = temp3->suit[0];
        temp2->face = temp3->face;
    
    }
    FreeDeck(&temp1);
    FreeDeck(&temp2);
    FreeDeck(&temp3);
}

void FreeDeck(card** hp){
    card* temp = *hp;
    while(temp != NULL){
        temp = temp->next;
        free(temp);
    }
    *hp = temp;
}
