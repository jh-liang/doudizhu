//
// Created by zxj on 2020/1/14.
//

#ifndef DOUDIZHU_FUNCTION_H
#define DOUDIZHU_FUNCTION_H

#include "stdio.h"
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include "struct.h"
#include <time.h>

card* shuffle(card *deck);
//used to shuffle at the beginning of the game

player distributing(card *deck, player playerx);
//distributing cards to players.

card* shufflethefirstthree(card *deck, card *firstthree);
//used to shuffle the first three load card at the beginning.

player aftercallingload(player playerx, card firstthree[3]);
//a response action to the player which become load

card* ordering(card *cards);
//used to make the card group in order

current NPCshow(player playerx, current currentcard);
//NPC showing card

current NPCshow_othernoshow(player playerx, current currentcard);

player aftershowing(player playerx, current currentcard);
//response to NPCshow

int countcard(card *cards);
//an action to count the amount or cards in a card group

card *find(card*show, card *currentcard, card *handcard);

int printcurrentcard(player playerx, card *currentcard);

card *findconst(card* show, const card sample[], card *handcard, int length);


int givingout_cards(player player1, player player2, player player3, current currentcard);

int givingout_cards_sub_1(player player1, player player2, player player3, current currentcard);

int givingout_cards_sub_2_3(player player1, player playerx1, player playerx2, current currentcard);


#endif //DOUDIZHU_FUNCTION_H

extern const card row_sample_5[5];
extern const card row_sample_6[6];
extern const card row_sample_7[7];
extern const card row_sample_8[8];
extern const card row_sample_9[9];
extern const card row_sample_10[10];
extern const card row_sample_11[11];
extern const card row_sample_12[12];
extern const card bombplustwo_sample[6];
extern const card bombplustwo_sample_2[6];
extern const card bombplustwo_sample_3[6];
extern const card bombplustwo_sample_4[6];
extern const card tripair_sample[6];
extern const card quapair_sample[8];
extern const card pentapair_sample[10];

extern const card twotriple_sample[6];
extern const card threetriple_sample[9];
extern const card threeplustwo_sample_1[5];
extern const card threeplustwo_sample_2[5];