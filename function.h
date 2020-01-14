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

int aftercallingload(player playerx, card firstthree[3]);

int ordering(int amount, card cards[amount]);

int show(player playerx, card currentcard[13]);

int countcard(int amount, card cards[20]);

int wannengrow(player playerx, card currentcard[13], int currentamount);

int find(int target, int array[], int position);

#endif //DOUDIZHU_FUNCTION_H
