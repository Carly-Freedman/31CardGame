#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <wchar.h>
#include "GameInfoGetters.h"

double AdjustBalance(int gameStatus, double balance, double bet);
void AdjustStats(int gameStatus, stat* gameStats);
void AdjustBalances2Player(int gameStatus, double* balance1, double* balance2, double* bet1, double* bet2);


double AdjustBalance(int gameStatus, double balance, double bet){
    double newBalance;
    if(gameStatus == 1 || gameStatus == -3){
        newBalance = balance + bet;
    }
    else if(gameStatus == -1 || gameStatus == 4){
        newBalance = balance - bet;
    }
    else{
        newBalance = balance;
    }
    return newBalance;
}


void AdjustStats(int gameStatus, stat* gameStats){
    gameStats->numTotal++;
    if (gameStatus == 1 || gameStatus == -3){
        gameStats->numPWon++;
        if(gameStatus == -3){
            gameStats->numP14++;
        }
    }
    else if(gameStatus == -1 || gameStatus == 4){
        gameStats->numDWon++;
        if(gameStatus == 4){
            gameStats->numD27++;
        }
    }
}

void AdjustBalances2Player(int gameStatus, double* balance1, double* balance2, double* bet1, double* bet2){
    if(gameStatus == 21){
        *balance2 += *bet2;
        *balance1 -= *bet1;
    }
    else if(gameStatus == 7){
        *balance1 += *bet1;
        *balance2 -= *bet2;
    }
    else if(gameStatus == 4 || gameStatus == -1){
        *balance1 -= *bet1;
        *balance2 -= *bet2;
    }
    else if(gameStatus == 6 || gameStatus == 1){
        *balance1 += *bet1;
        *balance2 += *bet2;
    }
    
}