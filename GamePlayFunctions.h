//
//  GameFunctions.h
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
#include "DeckAccessMembers.h"
#include "GameInfoSetters.h"


void DealCard(card** deckHead, card** handHead);
void DealerTurn(card** deckHead, card** hp, int* gameStatus);
void PlayAutomaticRound(card** deckHead, card** hp, int* gameStatus);
void PlayerTurn(card** deckHead, card** hp, int* gameStatus);
void SinglePlayerGame(card* deckHead, FILE* inp);
void TwoPlayerGame(card* deckHead, FILE* inp);
void TwoPlayerAutomaticRound(card** deckHead, card** player1Hand, card** player2Hand, int* gameStatus);
void TwoPlayersTurns(card** deckHead, card** player1Hand, card** player2Hand, int* gameStatus);


void DealCard(card** deckHead, card** handHead){
    int tempVal;
    char tempSuit;
    char tempFace;
   card *tempDeck = (card*)malloc(sizeof(card));
    tempDeck = *deckHead;
    tempVal = tempDeck->value;
    tempSuit = tempDeck->suit[0];
    tempFace = tempDeck->face;
    LoadDeck(handHead, tempVal, tempSuit, tempFace);
    *deckHead = (*deckHead)->next;
    free(tempDeck);

}

void DealerTurn(card** deckHead, card** hp, int* gameStatus){
    int sum = 0;
    card* listp;
    listp = *hp;
    while((sum != 14) && (sum < 27)){
        DealCard(deckHead, &listp);
        if(listp->value == 1){
            if ((sum + 11 <= 31) || (sum + 1 != 14)){
                listp->value = 11;
            }
        }
        sum = HandSum(hp);
    }
    if(sum == 14){
        printf("Dealer hit 14! Player must hit 31 to win.\n");
        printf("\nDealer's Hand: \n");
        PrintDeck(hp);
        *gameStatus = 2;
        return;
    }
    else if((sum >= 27)  && (sum < 31)){
        printf("\nDealer's Hand: \n");
        (*hp)->direction = 1;
        PrintDeck(hp);
        *gameStatus = 0;
        return;
    }
    else if(sum == 31){
        printf("Dealer hit 31. Dealer wins.\n");
        printf("Dealer's Hand: \n");
        PrintDeck(hp);
        *gameStatus = -1;
        return;
    }
    else{
        printf("Dealer goes bust. Player wins!\n");
        printf("Dealer's Hand: \n");
        PrintDeck(hp);
        *gameStatus = 1;
        return;
    }
}


void PlayAutomaticRound(card** deckHead, card** hp, int* gameStatus){
    int sum = 0;
    card* listp;
    listp = *hp;
    
    while(sum < 31){
        DealCard(deckHead, &listp);
        sum = HandSum(hp);
        if(listp->value == 1){
            if ((sum + 11 <= 31) || (sum + 1 != 14)){
                listp->value = 11;
            }
        }
    }
    printf("\n Player's Hand:\n");
    PrintDeck(hp);
    if (sum == 31){
        printf("Player hits 31. Player wins.\n");
        *gameStatus = 1;
        return;
    }
    else{
        printf("Player goes bust. Dealer wins.\n");
        *gameStatus = -1;
        return;
    }
    
    
}

void PlayerTurn(card** deckHead, card** hp, int* gameStatus){
    int sum = 0;
    card* listp;
    listp = *hp;
    char choice;
    int tempNum = 0;
    
    printf("Hit (h) or Stand (s)?\n");
    scanf(" %c", &choice);
    if (choice == 'h'){
        do {
            DealCard(deckHead, &listp);
            if(listp->face == 'A'){
                while((tempNum != 1) && (tempNum != 11)){
                    printf("You drew an ace. Would you like it to count as 1 or 11?\n");
                    scanf("%d", &tempNum);
                }
                
                listp->value = tempNum;
                listp = listp->next;
            }
            printf("\nPlayer's Hand:\n");
            PrintDeck(hp);
            sum = HandSum(hp);
            if(sum >= 31 || sum == 14){
                break;
            }
            printf("Hit (h) or Stand (s)?\n");
            scanf(" %c", &choice);
        } while (choice == 'h');
    }
    sum = HandSum(hp);
    if (sum > 31){
        printf("Player goes bust. Dealer wins.\n");
        *gameStatus = 4;
        return;
    }
    else if(sum == 31){
        printf("Player hit 31. Player wins.\n");
        *gameStatus = 1;
        return;
    }
    else if(sum == 14){
        printf("Player hit 14. Player wins.\n");
        *gameStatus = -3;
    }
    else{
        *gameStatus = -2;
        return;
    }
}


void SinglePlayerGame(card* deckHead, FILE* inp){
    int roundCount = 0;
    const double START_BALANCE = 1000;
    double balance = START_BALANCE;
    card *dealerHand = NULL;
    card *playerHand = NULL;
    double bet = 0;
    int gameStatus;
    int cardsLeft;
    stat gameStats;
    char key;
    //initializing stats
    gameStats.numD27 = 0;
    gameStats.numDWon = 0;
    gameStats.numTotal = 0;
    gameStats.numPWon = 0;
    gameStats.numP14 = 0;
    
    while(balance > 20){
       

           //beginning round
           roundCount++;
           PrintRound(roundCount);
           
           
           //Player Gets First Card:
           DealCard(&deckHead, &playerHand);
           printf("Player's Hand:\n");
           PrintDeck(&playerHand);
       
           //Dealer Gets First Card:
           printf("Dealer's Hand:\n");
           DealCard(&deckHead, &dealerHand);
           dealerHand->direction = 1;
           PrintDeck(&dealerHand);
       

           
           GetBet(&bet, balance);
                   
                   
           DealerTurn(&deckHead, &dealerHand, &gameStatus);
           if(gameStatus == 2){
               PlayAutomaticRound(&deckHead, &playerHand, &gameStatus);
           }
           else if(gameStatus == 0){
               PlayerTurn(&deckHead, &playerHand, &gameStatus);
               if(gameStatus == -2){
                   EvaluateWinner(&dealerHand, &playerHand, &gameStatus);
               }
               else{
                   printf("\n Dealer's Hand:\n");
                   PrintDeck(&dealerHand);
               }
           }
           AdjustStats(gameStatus, &gameStats);
           balance = AdjustBalance(gameStatus, balance, bet);
           PrintBalance(balance);
           
           FreeDeck(&dealerHand);
           FreeDeck(&playerHand);
           
           cardsLeft = countCards(&deckHead);
           if(cardsLeft <= 30){
               rewind(inp);
               FreeDeck(&deckHead);
               MakeDecks(inp, &deckHead);
               ShuffleDeck(&deckHead);
           }
           
           printf("\n----------------------------------------------------------------------\n");
           if (balance >=20){
               printf("Would you like to see your stats (y/n)?\n");
               scanf(" %c", &key);
               if (key == 'y'){
                   PrintGameStats(gameStats);
               }
               printf("\nWould you like to continue playing (y/n)?\n");
               scanf(" %c", &key);
               if(key == 'n'){
                   break;
               }
           }
           printf("\n----------------------------------------------------------------------\n");
       }
    free(deckHead);
}

void TwoPlayerGame(card* deckHead, FILE* inp){
    int roundCount = 0;
    const double START_BALANCE = 1000;
    double balance1 = START_BALANCE, balance2 = START_BALANCE;
    card *dealerHand = NULL;
    card *player1Hand = NULL;
    card *player2Hand = NULL;
    double bet1 = 0, bet2 = 0;
    int gameStatus;
    int cardsLeft;
    char key;
    
    while(balance1 >= 20 && balance2 >= 20){
    

        //beginning round
        roundCount++;
        PrintRound(roundCount);
        
        
        //Player1 Gets First Card:
        DealCard(&deckHead, &player1Hand);
        printf("Player 1's Hand:\n");
        PrintDeck(&player1Hand);
        
        //Player2 Gets First Card:
        DealCard(&deckHead, &player2Hand);
        printf("Player 2's Hand:\n");
        PrintDeck(&player2Hand);
        
        //Dealer Gets First Card:
        printf("Dealer's Hand:\n");
        DealCard(&deckHead, &dealerHand);
        dealerHand->direction = 1;
        PrintDeck(&dealerHand);
        

        printf("Player 1 ");
        GetBet(&bet1, balance1);
        printf("Player 2 ");
        GetBet(&bet2, balance2);
        
        DealerTurn(&deckHead, &dealerHand, &gameStatus);
        
        if(gameStatus == 2){
            TwoPlayerAutomaticRound(&deckHead, &player1Hand, &player2Hand, &gameStatus);
        }
        else if(gameStatus == 0){
            TwoPlayersTurns(&deckHead, &player1Hand, &player2Hand, &gameStatus);
            if(gameStatus == 8 || gameStatus == 15){
                EvaluateWinner2Player(&dealerHand, &player1Hand, &gameStatus);
            }
            else if (gameStatus == 10){
                EvaluateWinner2Player(&dealerHand, &player2Hand, &gameStatus);
            }
        }
        
        AdjustBalances2Player(gameStatus, &balance1, &balance2, &bet1, &bet2);
        printf("Player 1 ");
        PrintBalance(balance1);
        printf("Player 2 ");
        PrintBalance(balance2);
        
        FreeDeck(&player1Hand);
        FreeDeck(&player2Hand);
        FreeDeck(&dealerHand);
        
        cardsLeft = countCards(&deckHead);
        if(cardsLeft <= 30){
            rewind(inp);
            FreeDeck(&deckHead);
            MakeDecks(inp, &deckHead);
            ShuffleDeck(&deckHead);
        }
        if(balance1 > 20 && balance2 > 20){
            printf("\n----------------------------------------------------------------------\n");
        
            printf("\nWould you like to continue playing (y/n)?\n");
            scanf(" %c", &key);
            if(key == 'n'){
                break;
            }
        
        
            printf("\n----------------------------------------------------------------------\n");
        }
    }
    free(deckHead);
        
}

void TwoPlayerAutomaticRound(card** deckHead, card** player1Hand, card** player2Hand, int* gameStatus){
    int sum1 = 0, sum2 = 0;
    card *listp1, *listp2;
    listp1 = *player1Hand;
    listp2 = *player2Hand;
    
    while(sum1 < 31){
        DealCard(deckHead, &listp1);
        sum1 = HandSum(player1Hand);
        if(listp1->value == 1){
            if ((sum1 + 11 <= 31) || (sum1 + 1 != 14)){
                listp1->value = 11;
            }
        }
    }
    while(sum2 < 31){
        DealCard(deckHead, &listp2);
        sum2 = HandSum(player2Hand);
        if(listp2->value == 1){
            if ((sum2 + 11 <= 31) || (sum2 + 1 != 14)){
                listp1->value = 11;
            }
        }
        
    }
    printf("\n Player 1's Hand:\n");
    PrintDeck(player1Hand);
    
    printf("\nPlayer 2's Hand:\n");
    PrintDeck(player2Hand);
    
    if(sum1 == 31 && sum2 == 31){
        printf("Both players hit 31. Both players win.\n");
        *gameStatus = 6;
        return;
    }
    if (sum1 == 31){
        printf("Player 1 hits 31. Player 1 wins.\n");
        *gameStatus = 7;
        return;
    }
    if(sum2 == 31){
        printf("Player 2 hits 31. Player 2 wins.\n");
        *gameStatus = 21;
        return;
    }
    if(sum1 > 31 && sum2 > 31){
        printf("Both players go bust. Both players lose.\n");
        *gameStatus = 4;
        return;
    }
    if( sum1 > 31){
        printf("Player 1 goes bust. Player 2 and dealer win.\n");
        *gameStatus = 21;
        return;
    }
    if(sum2 > 31){
        printf("Player 2 goes bust. Player 1 and dealer win.\n");
        *gameStatus = 7;
        return;
    } 
}

void TwoPlayersTurns(card** deckHead, card** player1Hand, card** player2Hand, int* gameStatus){
    int sum1 = 0, sum2 = 0;
    card *listp1, *listp2;
    listp1 = *player1Hand;
    listp2 = *player2Hand;
    char choice1 = 'h', choice2 = 'h';
    int tempNum = 0;
    
    while((sum1 <= 31 || sum2<= 31) && (choice1 == 'h' || choice2 == 'h')){
        
    
        //Player 1 goes
        
        if (choice1 == 'h'){
            printf("Player 1 Hit (h) or Stand (s)?\n");
            scanf(" %c", &choice1);
            DealCard(deckHead, &listp1);
            if(listp1->face == 'A'){
                while((tempNum != 1) && (tempNum != 11)){
                    printf("You drew an ace. Would you like it to count as 1 or 11?\n");
                    scanf("%d", &tempNum);
                }
                
                listp1->value = tempNum;
                listp1 = listp1->next;
            }
            printf("\nPlayer 1's Hand:\n");
            PrintDeck(player1Hand);
            sum1 = HandSum(player1Hand);
        }
    
        //Player 2 goes
        
    
        if (choice2 == 'h'){
            printf("Player 2 Hit (h) or Stand (s)?\n");
            scanf(" %c", &choice2);
            DealCard(deckHead, &listp2);
            if(listp2->face == 'A'){
                while((tempNum != 1) && (tempNum != 11)){
                    printf("You drew an ace. Would you like it to count as 1 or 11?\n");
                    scanf("%d", &tempNum);
                }
                
                listp2->value = tempNum;
                listp2 = listp2->next;
            }
            printf("\nPlayer 2's Hand:\n");
            PrintDeck(player2Hand);
            sum2 = HandSum(player2Hand);
        }
    }
    
    
    
    sum1 = HandSum(player1Hand);
    sum2 = HandSum(player2Hand);
    
    if (sum1 > 31 && sum2 > 31){
        printf("Both players go bust. Dealer wins.\n");
        *gameStatus = 4;
    }
    else if(sum1 > 31){
        printf("Player 1 goes bust. ");
        if(sum2 == 31){
            printf("Player 2 hit 31. Player 2 wins.\n");
            *gameStatus = 21;
        }
        else{
            *gameStatus = 10;
        }
        return;
    }
    
    else if(sum2 > 31){
        printf("Player 2 goes bust. ");
        if(sum1 == 31){
            printf("Player 1 hit 31. Player 1 wins.\n");
            *gameStatus = 7;
        }
        else{
            *gameStatus = 8;
        }
    }
    
    if(sum1 == 31 && sum2 == 31){
        printf("Both players got 31. Both players win.\n");
        *gameStatus = 6;
    }
   
    if(sum1 < 31){
        if(sum2 < 31){
            if (sum1 > sum2){
                printf("Player 1 got %d and Player 2 got %d. Player 1 wins.\n", sum1, sum2);
                *gameStatus = 1;
            }
            else if(sum1 == sum2){
                *gameStatus = 15;
            }
        }
        else{
            *gameStatus = 8;
        }
    }
    else if (sum2 < 31){
        *gameStatus = 10;
    }
}










