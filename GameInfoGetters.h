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


void PrintRound(int count);
void PrintBalance(double balance);
void GetBet(double* bet, double balance);
void EvaluateWinner(card** dealerHand, card** playerHand, int* gameStatus);
void PrintRules(FILE* rules);
void PrintGameStats(stat gameStats);
void PrintGameOver(FILE* gameOver);
void EvaluateWinner2Player(card** hand1, card** hand2, int* gameStatus);


void PrintRound(int count){
    printf("\nRound: %d\n", count);
}

void PrintBalance(double balance){
    printf("Current Balance: $%.2lf\n", balance);
}

void GetBet(double* bet, double balance){
    *bet = 0;
    const double MAX_BET = 200;
    const double MIN_BET = 20;
    while((*bet > MAX_BET) || (*bet < MIN_BET) || (*bet > balance)){
        printf("Place bet:\n");
        scanf("%lf", bet);
    }
    
}

void EvaluateWinner(card** dealerHand, card** playerHand, int* gameStatus){
    int dSum, pSum;
    dSum = HandSum(dealerHand);
    pSum = HandSum(playerHand);
    
    printf("Dealer's Hand:\n");
    PrintDeck(dealerHand);
    
    printf("Dealer got %d, and Player got %d. ", dSum, pSum);
    if (pSum > dSum){
        printf("Player wins.\n");
        *gameStatus = 1;
    }
    else if (pSum < dSum){
        printf("Dealer wins.\n");
        *gameStatus = 4;
    }
    else{
        printf("Tie.\n Bet Pushed.\n");
        *gameStatus = 3;
    }
}


void PrintRules(FILE* rules){
    char tempChar;
    while(fscanf(rules, "%c", &tempChar) != EOF){
        printf("%c", tempChar);
    }
}


void PrintGameStats(stat gameStats){
    FILE* statsArt;
    char tempChar;
    statsArt = fopen("StatsArt.txt", "r");
    while(fscanf(statsArt, "%c", &tempChar) != EOF){
        printf("%c", tempChar);
}
    fclose(statsArt);
    printf("\n");
    printf("Number of games played in total..........................%d\n", gameStats.numTotal);
    printf("Percentage of games won by player in total...............%.2lf\n", 100.0 * ((double)gameStats.numPWon / (double)gameStats.numTotal));
    printf("Percentage of games won by player by hitting 14..........%.2lf\n", 100.0 * ((double)gameStats.numP14 / (double)gameStats.numTotal));
    printf("Percentage of games won by dealer in total...............%.2lf\n", 100.0 * ((double)gameStats.numDWon / (double)gameStats.numTotal));
    printf("Percentage of games won by dealer by hitting 27+.........%.2lf\n", 100.0 * ((double)gameStats.numD27 / (double)gameStats.numTotal));
    printf("___________________________________________________________________________________");
}
    
void PrintGameOver(FILE* gameOver){
    char tempChar;
    gameOver = fopen("GameOverGraphic.txt", "r");
    while(fscanf(gameOver, "%c", &tempChar)!= EOF){
        printf("%c", tempChar);
    }
}


void EvaluateWinner2Player(card** hand1, card** hand2, int* gameStatus){
    int sum1, sum2;
    sum1 = HandSum(hand1);
    sum2 = HandSum(hand2);
    
    if(*gameStatus == 8){
        printf("Dealer got %d and player 1 got %d. ", sum1, sum2);
        if(sum1 > sum2){
            printf("Dealer wins.\n");
            *gameStatus = 4;
        }
        else if(sum1 < sum2){
            printf("Player 1 wins.\n");
            *gameStatus = 7;
        }
        else{
            printf("Tie. Bet pushed.\n");
            *gameStatus = 9;
        }
    }
    else if(*gameStatus == 10){
       printf("Dealer got %d and player 2 got %d. ", sum1, sum2);
            if(sum1 > sum2){
                printf("Dealer wins.\n");
                *gameStatus = 4;
            }
            else if(sum1 < sum2){
                printf("Player 2 wins.\n");
                *gameStatus = 21;
            }
            else{
                printf("Tie. Bet pushed.\n");
                *gameStatus = 9;
            }
        }
    else if (*gameStatus == 15){
        printf("Dealer got %d and players 1 and 2 both got %d. ", sum1, sum2);
        if(sum1 > sum2){
            printf("Dealer wins.\n");
            *gameStatus = 4;
        }
        else if(sum1 < sum2){
            printf("Players 1 and 2 both win.\n");
            *gameStatus = 6;
        }
        else{
            printf("Tie. Bet pushed.\n");
            *gameStatus = 9;
        }
    }
}