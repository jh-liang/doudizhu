//
// Created by zxj on 2020/1/14.
//

#ifndef DOUDIZHU_FUNCTION_H
#define DOUDIZHU_FUNCTION_H

#include "stdio.h"
#include <math.h>
#include <stdlib.h>
#include "struct.h"

card* shuffle(card *deck);
//used to shuffle at the beginning of the game

player distributing(card *deck, player playerx, int playercode);
//distributing cards to players.

card* shufflethefirstthree(card *deck, card *firstthree);
//used to shuffle the first three load card at the beginning.

player aftercallingload(player playerx, card firstthree[3]);
//a response action to the player which become load

card* ordering(card *cards);
//used to make the card group in order

card* NPCshow(player playerx, card *currentcard);
//NPC showing card

int countcard(card cards[20]);
//an action to count the amount or cards in a card group

int wannengrow(player playerx, card currentcard[13], int currentamount);
//row of any number >= 5

int findpos(int target, int cardarray[]);
//find the position of a card in a cardgroup

card *find(card *currentcard, card *handcard);

int printcurrentcard(player playerx, card *currentcard);

#endif //DOUDIZHU_FUNCTION_H
