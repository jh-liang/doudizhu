//
// Created by zxj on 2020/1/14.
//

#ifndef DOUDIZHU_FUNCTION_H
#define DOUDIZHU_FUNCTION_H

#include "stdio.h"
#include <math.h>
#include <stdlib.h>
#include "struct.h"

int shuffle(card deck[54], player player1, player player2, player player3, card firstthree[3]);
//used to shuffle at the beginning of the game

int aftercallingload(player playerx, card firstthree[3]);
//a response action to the player which become load

int ordering(int amount, card cards[amount]);
//used to make the card group in order

int NPCshow(player playerx, card currentcard[13], int othernoshow);
//NPC showing card

int countcard(card cards[20]);
//an action to count the amount or cards in a card group

int wannengrow(player playerx, card currentcard[13], int currentamount);
//row of any number >= 5

int findpos(int target, int cardarray[], int position);
//find the position of a card in a cardgroup

int find(card target[20], card from[20]);

int printcurrentcard(player playerx, card currentcard[13]);

#endif //DOUDIZHU_FUNCTION_H
