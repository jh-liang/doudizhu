//
// Created by zxj on 2020/1/14.
//

#include "function.h"

const card row_sample_5[5] = {
        {"diamond", 1, 1}, {"diamond", 2, 5}, {"diamond", 3, 9},
        {"diamond", 4, 13}, {"diamond", 5, 17}};
const card row_sample_6[6] = {
        {"diamond", 1, 1}, {"diamond", 2, 5}, {"diamond", 3, 9},
        {"diamond", 4, 13}, {"diamond", 5, 17}, {"diamond", 6, 21}};
const card row_sample_7[7] = {
        {"diamond", 1, 1}, {"diamond", 2, 5}, {"diamond", 3, 9},
        {"diamond", 4, 13}, {"diamond", 5, 17}, {"diamond", 6, 21},
        {"diamond", 7, 25}};
const card row_sample_8[8] = {
        {"diamond", 1, 1}, {"diamond", 2, 5}, {"diamond", 3, 9},
        {"diamond", 4, 13}, {"diamond", 5, 17}, {"diamond", 6, 21},
        {"diamond", 7, 25}, {"diamond", 8, 29}};
const card row_sample_9[9] = {
        {"diamond", 1, 1}, {"diamond", 2, 5}, {"diamond", 3, 9},
        {"diamond", 4, 13}, {"diamond", 5, 17}, {"diamond", 6, 21},
        {"diamond", 7, 25}, {"diamond", 8, 29}, {"diamond", 9, 33}};
const card row_sample_10[10] = {
        {"diamond", 1, 1}, {"diamond", 2, 5}, {"diamond", 3, 9},
        {"diamond", 4, 13}, {"diamond", 5, 17}, {"diamond", 6, 21},
        {"diamond", 7, 25}, {"diamond", 8, 29}, {"diamond", 9, 33},
        {"diamond", 10, 37}};
const card row_sample_11[11] = {
        {"diamond", 1, 1}, {"diamond", 2, 5}, {"diamond", 3, 9},
        {"diamond", 4, 13}, {"diamond", 5, 17}, {"diamond", 6, 21},
        {"diamond", 7, 25}, {"diamond", 8, 29}, {"diamond", 9, 33},
        {"diamond", 10, 37}, {"diamond", 11, 41}};
const card row_sample_12[12] = {
        {"diamond", 1, 1}, {"diamond", 2, 5}, {"diamond", 3, 9},
        {"diamond", 4, 13}, {"diamond", 5, 17}, {"diamond", 6, 21},
        {"diamond", 7, 25}, {"diamond", 8, 29}, {"diamond", 9, 33},
        {"diamond", 10, 37}, {"diamond", 11, 41},{"diamond", 12, 45}};
const card bombplustwo_sample[6] = {
        {"diamond", 1, 1}, {"club", 1, 2}, {"heart", 1, 3},
        {"spade", 1, 4}, {"diamond", 2, 5}, {"club", 2, 6}};
const card bombplustwo_sample_2[6] = {
        {"diamond", 1, 1}, {"club", 1, 2}, {"heart", 1, 3},
        {"spade", 1, 4}, {"diamond", 2, 5}, {"diamond", 3, 9}};
const card bombplustwo_sample_3[6] = {
        {"diamond", 2, 5}, {"club", 2, 6}, {"heart", 2, 7},
        {"spade", 2, 8}, {"diamond", 1, 1}, {"diamond", 3, 9}};
const card bombplustwo_sample_4[6] = {
        {"diamond", 3, 9}, {"club", 3, 10}, {"heart", 3, 11},
        {"spade", 3, 12}, {"diamond", 1, 1}, {"diamond", 2, 5}};
const card tripair_sample[6] = {
        {"diamond", 1, 1}, {"club", 1, 2}, {"diamond", 2, 5},
        {"club", 2, 6}, {"diamond", 3, 9}, {"club", 3, 10}};
const card quapair_sample[8] = {
        {"diamond", 1, 1}, {"club", 1, 2}, {"diamond", 2, 5},
        {"club", 2, 6}, {"diamond", 3, 9}, {"club", 3, 10},
        {"diamond", 4, 13}, {"club", 4, 14}};
const card pentapair_sample[10] = {
        {"diamond", 1, 1}, {"club", 1, 2}, {"diamond", 2, 5},
        {"club", 2, 6}, {"diamond", 3, 9}, {"club", 3, 10},
        {"diamond", 4, 13}, {"club", 4, 14}, {"diamond", 5, 17},
        {"club", 5, 18}};
const card twotriple_sample[6] = {
        {"diamond", 1, 1}, {"club", 1, 2}, {"heart", 1, 3},
        {"diamond", 2, 5}, {"club", 2, 6}, {"heart", 2, 7}};
const card threetriple_sample[9] = {
        {"diamond", 1, 1}, {"club", 1, 2}, {"heart", 1, 3},
        {"diamond", 2, 5}, {"club", 2, 6}, {"heart", 2, 7},
        {"diamond", 3, 9}, {"club", 3, 10}, {"heart", 3, 11},};
const card threeplustwo_sample_1[5] = {
        {"diamond", 1, 1}, {"club", 1, 2}, {"heart", 1, 3},
        {"diamond", 2, 5}, {"club", 2, 6}};
const card threeplustwo_sample_2[5] = {
        {"diamond", 1, 1}, {"club", 1, 2}, {"diamond", 2, 5},
        {"club", 2, 6}, {"heart", 2, 7}};


card* shuffle(card *deck) {     //开局洗牌
    for (int j = 0; j <= 3 ; j++){            //现在大小是1-13 没有AJQK 懒 以后再弄
        for (int i = 0; i <= 12; i++) {
            deck[i + j*13].num = i + 1;
            deck[i + j*13].code = i + j * 13 + 1;
        }
    }

    for (int i = 0; i <= 12; i++) {
        deck[i].patt = "diamond";
        deck[i + 13].patt = "club";
        deck[i + 26].patt = "heart";
        deck[i + 39].patt = "spade";
    }

    deck[52].code = 53;
    deck[52].num = 14;
    deck[52].patt = "joker";               //小王
    deck[53].code = 54;
    deck[53].num = 15;
    deck[53].patt = "joker";               //大王

    int sequence[54];
    for (int i = 0; i <= 53; i++) {
        sequence[i] = i;
    }

    srand(time(NULL));
    for (int i = 0; i <= 53; i++) {             //弄一个sequence数组，用rand函数把sequence里的数字交换54次
        int a = rand() % 53;
        int X = sequence[a];
        sequence[a] = sequence[i];
        sequence[i] = X;
    }

    card *XX = calloc(54, sizeof(card));
    for (int i = 0; i <= 53; i++) {             //把sequence代入deck里面，shuffled = 洗好的牌
        XX[i].code = deck[sequence[i]].code;
        XX[i].num = deck[sequence[i]].num;
        XX[i].patt = deck[sequence[i]].patt;
    }

    for (int i = 0; i <= 53; i++){
        deck[i].code = XX[i].code;
        deck[i].patt = XX[i].patt;
        deck[i].num = XX[i].num;
    }
    free(XX);
    return deck;
}

player distributing(card* deck, player playerx) {
    for (int i = 0; i <= 16; i++) {
        playerx.hand[i] = deck[i + (playerx.code - 1) * 17];
    }
    for (int i = 0; i <= 16; i++) {
        if (playerx.hand[i].code == 15){
            playerx.role = "Load";
            break;
        }
        else playerx.role = "Farmer";
    }
    memset(playerx.hand+17, 0, 3 * sizeof(card));
    playerx.hand = ordering(playerx.hand);
    return playerx;
}

card* shufflethefirstthree(card *deck, card *firstthree){
    for (int i = 0; i <= 2; i++) {
        firstthree[i] = deck[i + 51];
    }
    firstthree = ordering(firstthree);
    return firstthree;
}

player aftercallingload(player playerx, card *firstthree) {       //叫完地主后派地主牌
    playerx.hand[17] = firstthree[0];
    playerx.hand[18] = firstthree[1];
    playerx.hand[19] = firstthree[2];
    playerx.numofhand+=3;
    playerx.hand = ordering(playerx.hand);
    return playerx;
}

//FIXME: 改循环的判定条件，上面已经帮你改过几个了
card* ordering(card *cards){           //排序牌组
    int amount = countcard(cards);
    for (int j = amount - 1; j >= 0; j--) {
        for (int i = 0; i <= j - 1; i++) {
            if (cards[i + 1].code > cards[i + 2].code){
                card cardsx = cards[i + 1];
                cards[i + 1] = cards[i];
                cards[i] = cardsx;
            }
        }
    }
    for (int j = amount - 1; j >= 0; j--){
        for (int i = 0; i <= j - 1; i++) {
            if (cards[i].num > cards[i + 1].num){
                card cardsx = cards[i + 1];
                cards[i + 1] = cards[i];
                cards[i] = cardsx;
            }
        }
    }
    return cards;
}

current NPCshow(player playerx, current currentcard){
    card *show = calloc(20, sizeof(card));
    int amount = countcard(currentcard.cards);

    if (currentcard.special == 0){     //单牌、对子、三张、顺子、连对、飞机、三带二
        if (amount > 3) {
            show = find(show, currentcard.cards, playerx.hand);

            for (int i = 0; i <= 16; i++) {
                printf("~~~show %d,,%d,,%s'''''''''playerx %d,,%s''''\n", i + 1, show[i].num, show[i].patt,
                       playerx.hand[i].num, playerx.hand[i].patt);
            }

            if (show[0].num == 0) {
                currentcard.state_playercannotout = 1;
            }
            else {
                currentcard.state_playercannotout = 0;
                for (int i = 0; i <= 19; i++) {
                    currentcard.cards[i].patt = show[i].patt;
                    currentcard.cards[i].num = show[i].num;
                    currentcard.cards[i].code = show[i].code;
                }
            }
        }
        else if (amount == 3) {
            for (int i = 0; i <= amount - 3; i++) {
                if (playerx.hand[i].num > currentcard.cards[0].num
                    && playerx.hand[i].num == playerx.hand[i + 1].num
                    && playerx.hand[i + 1].num == playerx.hand[i + 2].num) {
                    memset(currentcard.cards, 0, 20 * sizeof(card));
                    for (int j = 0; j <= 2; j++) {
                        currentcard.cards[j].patt = playerx.hand[i + j].patt;
                        currentcard.cards[j].num = playerx.hand[i + j].num;
                        currentcard.cards[j].code = playerx.hand[i + j].code;
                    }
                    for (int j = 0; j <= 2; j++) {
                        for (int k = i + j; k <= 19; k++) {
                            playerx.hand[k].patt = playerx.hand[k + 1].patt; playerx.hand[k].num = playerx.hand[k + 1].num; playerx.hand[k].code = playerx.hand[k + 1].code;
                        }
                        memset(playerx.hand + countcard((playerx.hand)), 0, sizeof(card));
                    }
                    currentcard.state_playercannotout = 0;
                    for (int f = 0; f <= 16; f++) {
                        printf("~~~show %d,,%d,,%s'''''''''playerx %d,,%s''''\n", f + 1, currentcard.cards[f].num, currentcard.cards[f].patt,
                               playerx.hand[i].num, playerx.hand[i].patt);
                    }
                    break;
                }
                else currentcard.state_playercannotout = 1;
            }
        }
        else if (amount == 2) {
            for (int i = 0; i <= amount - 2; i++) {
                if (playerx.hand[i].num > currentcard.cards[0].num
                    && playerx.hand[i].num == playerx.hand[i + 1].num) {
                    memset(currentcard.cards, 0, 20 * sizeof(card));
                    for (int j = 0; j <= 1; j++) {
                        currentcard.cards[j].patt = playerx.hand[i + j].patt;
                        currentcard.cards[j].num = playerx.hand[i + j].num;
                        currentcard.cards[j].code = playerx.hand[i + j].code;
                    }
                    for (int j = 0; j <= 1; j++) {
                        for (int k = i + j; k <= 19; k++) {
                            playerx.hand[k].patt = playerx.hand[k + 1].patt; playerx.hand[k].num = playerx.hand[k + 1].num; playerx.hand[k].code = playerx.hand[k + 1].code;
                        }
                        memset(playerx.hand + countcard((playerx.hand)), 0, sizeof(card));
                    }
                    for (int f = 0; f <= 16; f++) {
                        printf("~~~show %d,,%d,,%s'''''''''playerx %d,,%s''''\n", f + 1, currentcard.cards[f].num, currentcard.cards[f].patt,
                               playerx.hand[i].num, playerx.hand[i].patt);
                    }
                    currentcard.state_playercannotout = 0;
                    break;
                }
                else currentcard.state_playercannotout = 1;
            }
        }
        else if (amount == 1) {
            for (int i = 0; i <= amount - 1; i++) {
                if (playerx.hand[i].num > currentcard.cards[0].num
                    && playerx.hand[i].num != playerx.hand[i+1].num) {
                    memset(currentcard.cards, 0, 20 * sizeof(card));
                    currentcard.cards[0].patt = playerx.hand[i].patt;
                    currentcard.cards[0].num = playerx.hand[i].num;
                    currentcard.cards[0].code = playerx.hand[i].code;
                    for (int k = i; k <= 19; k++) {
                        playerx.hand[k].patt = playerx.hand[k + 1].patt; playerx.hand[k].num = playerx.hand[k + 1].num; playerx.hand[k].code = playerx.hand[k + 1].code;
                    }
                    memset(playerx.hand + countcard((playerx.hand)), 0, sizeof(card));
                    currentcard.state_playercannotout = 0;
                    break;
                }
                else currentcard.state_playercannotout = 1;
            }
        }
    }
    free(show);
    return currentcard;
}

current NPCshow_othernoshow(player playerx, current currentcard){
    int amount = countcard(playerx.hand);
    currentcard.state_playercannotout = 0;
    memset(currentcard.cards, 0, 20*sizeof(card));

    currentcard.cards = findconst(currentcard.cards, row_sample_12, playerx.hand, 12);
    if (currentcard.cards[0].num != 0) return currentcard;
    currentcard.cards = findconst(currentcard.cards, row_sample_11, playerx.hand, 11);
    if (currentcard.cards[0].num != 0) return currentcard;
    currentcard.cards = findconst(currentcard.cards, row_sample_10, playerx.hand, 10);
    if (currentcard.cards[0].num != 0) return currentcard;


    currentcard.cards = findconst(currentcard.cards, threetriple_sample, playerx.hand, 9);
    if (currentcard.cards[0].num != 0) return currentcard;
    currentcard.cards = findconst(currentcard.cards, twotriple_sample, playerx.hand, 6);
    if (currentcard.cards[0].num != 0) return currentcard;
    currentcard.cards = findconst(currentcard.cards, pentapair_sample, playerx.hand, 10);
    if (currentcard.cards[0].num != 0) return currentcard;
    currentcard.cards = findconst(currentcard.cards, quapair_sample, playerx.hand, 8);
    if (currentcard.cards[0].num != 0) return currentcard;
    currentcard.cards = findconst(currentcard.cards, tripair_sample, playerx.hand, 6);
    if (currentcard.cards[0].num != 0) return currentcard;

    currentcard.cards = findconst(currentcard.cards, threeplustwo_sample_1, playerx.hand, 5);
    if (currentcard.cards[0].num != 0) return currentcard;
    currentcard.cards = findconst(currentcard.cards, threeplustwo_sample_2, playerx.hand, 5);
    if (currentcard.cards[0].num != 0) return currentcard;

    currentcard.cards = findconst(currentcard.cards, row_sample_9, playerx.hand, 9);
    if (currentcard.cards[0].num != 0) return currentcard;
    currentcard.cards = findconst(currentcard.cards, row_sample_8, playerx.hand, 8);
    if (currentcard.cards[0].num != 0) return currentcard;
    currentcard.cards = findconst(currentcard.cards, row_sample_7, playerx.hand, 7);
    if (currentcard.cards[0].num != 0) return currentcard;
    currentcard.cards = findconst(currentcard.cards, row_sample_6, playerx.hand, 6);
    if (currentcard.cards[0].num != 0) return currentcard;
    currentcard.cards = findconst(currentcard.cards, row_sample_5, playerx.hand, 5);
    if (currentcard.cards[0].num != 0) return currentcard;

    if (amount == 6 && playerx.numofhand == 6) {
        currentcard.cards = findconst(currentcard.cards, bombplustwo_sample, playerx.hand, 6);
        if (currentcard.cards[0].num != 0) return currentcard;
        currentcard.cards = findconst(currentcard.cards, bombplustwo_sample_2, playerx.hand, 6);
        if (currentcard.cards[0].num != 0) return currentcard;
        currentcard.cards = findconst(currentcard.cards, bombplustwo_sample_3, playerx.hand, 6);
        if (currentcard.cards[0].num != 0) return currentcard;
        currentcard.cards = findconst(currentcard.cards, bombplustwo_sample_4, playerx.hand, 6);
        if (currentcard.cards[0].num != 0) return currentcard;
    }

//    if (amount == 4 && playerx.numofhand <= 8) {
//        currentcard.cards = findconst(currentcard.cards, bomb_sample, playerx.hand, sizeof(bomb_sample)/sizeof(card));
//        if (currentcard.cards[0].num != 0) {
//            currentcard.cards = currentcard.cards;
//            printf("Checkpoint 4\n");
//            free(currentcard.cards); return currentcard;
//        }
//    }

    memset(currentcard.cards, 0, 20 * sizeof(card));

    for (int i = 0; i <= amount - 1; i++) {
        if (playerx.hand[i].num == playerx.hand[i + 1].num
            && playerx.hand[i + 1].num == playerx.hand[i + 2].num) {
            for (int f = 0; f <= 16; f++) {
                printf("~~~%d,,playerx %d,,%s''''\n", f + 1, playerx.hand[i].num, playerx.hand[i].patt);
            }
            for (int j = 0; j <= 2; j++) {
                printf("%d--->%d\n", i + j, playerx.hand[i + j].num);
                currentcard.cards[j].patt = playerx.hand[i + j].patt;
                currentcard.cards[j].num = playerx.hand[i + j].num;
                currentcard.cards[j].code = playerx.hand[i + j].code;
            }
            for (int j = 0; j <= 2; j++) {
                for (int k = i + j; k <= 19; k++) {
                    playerx.hand[k].patt = playerx.hand[k + 1].patt; playerx.hand[k].num = playerx.hand[k + 1].num; playerx.hand[k].code = playerx.hand[k + 1].code;
                }
                memset(playerx.hand + countcard((playerx.hand)), 0, sizeof(card));
            }
            for (int f = 0; f <= 16; f++) {
                printf("~~~show %d,,%d,,%s'''''''''playerx %d,,%s''''\n", f + 1, currentcard.cards[f].num, currentcard.cards[f].patt,
                       playerx.hand[i].num, playerx.hand[i].patt);
            }
            return currentcard;
        }
    }

    for (int i = 0; i <= amount - 1; i++) {
        if (playerx.hand[i].num == playerx.hand[i + 1].num) {
            for (int j = 0; j <= 1; j++) {
                currentcard.cards[j].patt = playerx.hand[i+j].patt;
                currentcard.cards[j].num = playerx.hand[i+j].num;
                currentcard.cards[j].code = playerx.hand[i+j].code;
            }
            for (int f = 0; f <= 16; f++) {
                printf("~~~%d,,playerx %d,,%s''''\n", f + 1, playerx.hand[i].num, playerx.hand[i].patt);
            }
            for (int j = 0; j <= 1; j++) {
                for (int k = i + j; k <= 19; k++) {
                    playerx.hand[k].patt = playerx.hand[k + 1].patt; playerx.hand[k].num = playerx.hand[k + 1].num; playerx.hand[k].code = playerx.hand[k + 1].code;
                }
                memset(playerx.hand + countcard((playerx.hand)), 0, sizeof(card));
            }
            for (int f = 0; f <= 16; f++) {
                printf("~~~show %d,,%d,,%s'''''''''playerx %d,,%s''''\n", f + 1, currentcard.cards[f].num, currentcard.cards[f].patt,
                       playerx.hand[i].num, playerx.hand[i].patt);
            }
            return currentcard;
        }
    }
    for (int i = 0; i <= amount - 1; i++) {
        if (playerx.hand[i].num < 8 && playerx.hand[i].num != playerx.hand[i+1].num) {
            currentcard.cards[0].patt = playerx.hand[i].patt;
            currentcard.cards[0].num = playerx.hand[i].num;
            currentcard.cards[0].code = playerx.hand[i].code;
            for (int k = i; k <= 19; k++) {
                playerx.hand[k].patt = playerx.hand[k + 1].patt; playerx.hand[k].num = playerx.hand[k + 1].num; playerx.hand[k].code = playerx.hand[k + 1].code;
            }
            memset(playerx.hand + countcard((playerx.hand)), 0, sizeof(card));
            return currentcard;
            for (int f = 0; f <= 16; f++) {
                printf("~~~show %d,,%d,,%s'''''''''playerx %d,,%s''''\n", f + 1, currentcard.cards[f].num, currentcard.cards[f].patt,
                       playerx.hand[i].num, playerx.hand[i].patt);
            }
        }
    }
    currentcard.special = 0;
    return currentcard;
}

player aftershowing(player playerx, current currentcard) {
//    int amount = countcard(currentcard.cards);
    playerx.numofhand = countcard(playerx.hand);
//    int pamount = countcard(playerx.hand);

    if (currentcard.state_playercannotout == 0){
//        for (int i = 0; i <= amount - 1; i++){
//            for (int j = 0; j <= pamount - 1; j++){
//                if (currentcard.cards[i].code == playerx.hand[j].code){
//                    for (int k = j; k <= (pamount-1); k++) {
//                        playerx.hand[k] = playerx.hand[k + 1];
//                    }
//                    memset(&playerx.hand[pamount - 1], 0, sizeof(card));
//                    pamount--;
//                    break;
//                }
//            }
//        }
        playerx.cannotshow = 0;
    }
    else playerx.cannotshow = 1;
    return playerx;
}

int countcard(card *cards){              //数牌
    int amount = 0;
    while (amount < 20) {
        if (cards[amount].num != 0) amount++;
        else break;
    }
    return amount;
}

card *find(card* show, card *currentcard, card *handcard){
    memset(show, 0, 20 * sizeof(card));
    int length = countcard(currentcard);
    int *pattern = calloc(length, sizeof(int));
    for (int i = 0; i <= length - 1; i++){
        pattern[i] = currentcard[i].num;
    }
    int *value = calloc(length, sizeof(int));
    int *quatity = calloc(length, sizeof(int));

    value[0] = pattern[0];
    quatity[0] = 1;

    int hh = 0;
    for (int i = 0; i <= (length - 2); i++){
        if (pattern[i] == pattern[i+1]){
            quatity[hh]++;
        }
        else {
            hh++;                            //hh = len of value and quatity
            value[hh] = pattern[i+1];
            quatity[hh] = 1;
        }
    }


    int pamount = countcard(handcard);
    int *ppattern = calloc(pamount, sizeof(int));
    for (int i = 0; i <= pamount - 1; i++){
        ppattern[i] = handcard[i].num;
    }
    int *pvalue = calloc(pamount, sizeof(int));
    int *pquatity = calloc(pamount, sizeof(int));

    pvalue[0] = pattern[0];
    pquatity[0] = 1;

    int phh = 0;
    for (int i = 0; i <= (pamount - 2); i++){
        if (ppattern[i] == ppattern[i+1]){
            pquatity[phh]++;
        }
        else {
            phh++;                            //hh = len of value and quatity
            pvalue[phh] = ppattern[i+1];
            pquatity[phh] = 1;
        }
    }

    int lhh = 0;
    int *lvalue = calloc(pamount, sizeof(int));
    int *lquatity = calloc(pamount, sizeof(int));
    for (int j = 0; j <= phh; j++){
        if (pvalue[j] > value[0]){
            for (int k = 0; k <= (phh - j); k++) {
                lquatity[k] = pquatity[j+k];
                lvalue[k] = pvalue[j+k];
            }
            lhh = phh - j;
            break;
        }
    }

    if (lhh < hh) {
        free(pattern); free(quatity); free(value);
        free(ppattern); free(pquatity); free(pvalue); free(lquatity); free(lvalue);
        return show;
    }

    int *dvalue = calloc(hh+1, sizeof(int));
    dvalue[0] = value[0];
    for (int i = 1; i <= hh; i++) {
        dvalue[i] = value[i] - value[i-1];
    }

    int *dlvalue = calloc(lhh + 1, sizeof(int));
    dlvalue[0] = lvalue[0];
    for (int i = 1; i <= lhh; i++) {
        dlvalue[i] = lvalue[i] - lvalue[i-1];
    }

    int *new = calloc(hh+1, sizeof(int));
    int nhh = 1;

    for (int i = 0; i <= (lhh - hh); i++){
        new[0] = lvalue[i];
        if (quatity[0] == lquatity[i] || quatity[0] + 1 == lquatity[i]) {
            for (int j = 1; j <= hh; j++) {
                if (dlvalue[i + j] == dvalue[j] &&
                    (quatity[j] == lquatity[i + j] || quatity[j] + 1 == lquatity[i + j])) {
                    new[j] = lvalue[i + j];
                    nhh++;
                }
                if (dvalue[j] == 0){
                    break;
                }
            }
        }
        nhh--;
        if (nhh == hh) break;
        else nhh = 1;
    }

    free(pattern); free(ppattern); free(pquatity); free(lquatity); free(value);
    free(pvalue); free(lvalue); free(dvalue); free(dlvalue);

    for (int j = 0; j <= hh; j++) {
        if (new[j] == 0){
            nhh = -1;
            break;
        }
    }

    if (nhh != hh){
        free(quatity); free(new);
        return show;
    }

    int *sum = calloc(hh+2, sizeof(int));
    sum[0] = 0;
    sum[1] = quatity[0];
    for (int i = 2; i <= hh+1; i++){
        sum[i] = sum[i -  1] + quatity[i - 1];
    }

    int *newarray = calloc(length, sizeof(int));
    for (int i = 0; i <= hh; i++){
        for (int k = sum[i]; k <= sum[i+1] - 1; k++){
            newarray[k] = new[i];
        }
    }

    for (int i = 0; i <= length - 1; i++){
        for (int j = 0; j <= pamount - 1; j++) {
            if (handcard[j].num == newarray[i]) {
                show[i] = handcard[j];
                for (int k = j; k <= (pamount-1); k++) {
                    handcard[k] = handcard[k + 1];
                }
                pamount--;
                //printcurrentcard(playerx, currentcard);
                memset(handcard + pamount, 0, sizeof(card));
                break;
            }
        }
    }
    free(sum); free(newarray); free(quatity); free(new);
    return show;
}

int printcurrentcard(player playerx, card *currentcard){
    int currentamount = countcard(currentcard);
    if (playerx.cannotshow == 1)printf("Player %d cannot give out cards.\n", playerx.code);
    else {
        printf("Player %d gives out %d card(s). Current card is (are)\n", playerx.code, currentamount);
        for (int i = 0; i <= currentamount - 1; i++) {
            printf("[%d] %s %d\n", i + 1, currentcard[i].patt, currentcard[i].num);
        }
    }
    printf("Player %d has %d cards left.\n", playerx.code, playerx.numofhand);
    return 0;
}

card *findconst(card* show, const card sample[], card *handcard, int length) {
    memset(show, 0, 20 * sizeof(card));
    int *pattern = calloc(length, sizeof(int));
    for (int i = 0; i <= length - 1; i++){
        pattern[i] = sample[i].num;
    }
    int *value = calloc(length, sizeof(int));
    int *quatity = calloc(length, sizeof(int));

    value[0] = pattern[0];
    quatity[0] = 1;

    int hh = 0;
    for (int i = 0; i <= (length - 2); i++){
        if (pattern[i] == pattern[i+1]){
            quatity[hh]++;
        }
        else {
            hh++;                            //hh = len of value and quatity
            value[hh] = pattern[i+1];
            quatity[hh] = 1;
        }
    }


    int pamount = countcard(handcard);
    int *ppattern = calloc(pamount, sizeof(int));
    for (int i = 0; i <= pamount - 1; i++){
        ppattern[i] = handcard[i].num;
    }
    int *pvalue = calloc(pamount, sizeof(int));
    int *pquatity = calloc(pamount, sizeof(int));

    pvalue[0] = pattern[0];
    pquatity[0] = 1;

    int phh = 0;
    for (int i = 0; i <= (pamount - 2); i++){
        if (ppattern[i] == ppattern[i+1]){
            pquatity[phh]++;
        }
        else {
            phh++;                            //hh = len of value and quatity
            pvalue[phh] = ppattern[i+1];
            pquatity[phh] = 1;
        }
    }

    int lhh = 0;
    int *lvalue = calloc(pamount, sizeof(int));
    int *lquatity = calloc(pamount, sizeof(int));
    for (int j = 0; j <= phh; j++){
        if (pvalue[j] >= value[0]){
            for (int k = 0; k <= (phh - j); k++) {
                lquatity[k] = pquatity[j+k];
                lvalue[k] = pvalue[j+k];
            }
            lhh = phh - j;
            break;
        }
    }

    if (lhh < hh) {
        free(pattern); free(quatity); free(value);
        free(ppattern); free(pquatity); free(pvalue); free(lquatity); free(lvalue);
        return show;
    }

    int *dvalue = calloc(hh+1, sizeof(int));
    dvalue[0] = value[0];
    for (int i = 1; i <= hh; i++) {
        dvalue[i] = value[i] - value[i-1];
    }

    int *dlvalue = calloc(lhh + 1, sizeof(int));
    dlvalue[0] = lvalue[0];
    for (int i = 1; i <= lhh; i++) {
        dlvalue[i] = lvalue[i] - lvalue[i-1];
    }

    int *new = calloc(hh+1, sizeof(int));
    int nhh = 1;

    for (int i = 0; i <= (lhh - hh); i++){
        new[0] = lvalue[i];
        if (quatity[0] == lquatity[i] || quatity[0] + 1 == lquatity[i]) {
            for (int j = 1; j <= hh; j++) {
                if (dlvalue[i + j] == dvalue[j] &&
                    (quatity[j] == lquatity[i + j] || quatity[j] + 1 == lquatity[i + j])) {
                    new[j] = lvalue[i + j];
                    nhh++;
                }
                if (dvalue[j] == 0){
                    break;
                }
            }
        }
        nhh--;
        if (nhh == hh) break;
        else nhh = 1;
    }

    free(pattern); free(ppattern); free(pquatity); free(lquatity); free(value);
    free(pvalue); free(lvalue); free(dvalue); free(dlvalue);

    for (int j = 0; j <= hh; j++) {
        if (new[j] == 0){
            nhh = -1;
            break;
        }
    }

    if (nhh != hh){
        free(quatity); free(new);
        return show;
    }

    int *sum = calloc(hh+2, sizeof(int));
    sum[0] = 0;
    sum[1] = quatity[0];
    for (int i = 2; i <= hh+1; i++){
        sum[i] = sum[i - 1] + quatity[i - 1];
    }

    int *newarray = calloc(length, sizeof(int));
    for (int i = 0; i <= hh; i++){
        for (int k = sum[i]; k <= sum[i+1] - 1; k++){
            newarray[k] = new[i];
        }
    }

    for (int i = 0; i <= length - 1; i++){
        for (int j = 0; j <= pamount - 1; j++) {
            if (handcard[j].num == newarray[i]) {
                show[i] = handcard[j];
                for (int k = j; k <= (pamount-1); k++) {
                    handcard[k] = handcard[k + 1];
                }
                pamount--;
                //printcurrentcard(playerx, currentcard);
                memset(handcard + pamount, 0, sizeof(card));
                break;
            }
        }
    }
    free(sum); free(newarray); free(quatity); free(new);
    return show;
}


//
//int givingout_cards(player player_1st, player player_2nd, player player_3rd, current currentcard){
//
//    printf("Player %d is trying to show cards.\n", player_1st.code);
//    if (player_1st.code == 1) givingout_cards_sub_2_3(player_1st, player_2nd, player_3rd, currentcard);
//    if (player_1st.code == 2 || player_1st.code == 3) givingout_cards_sub_2_3(player_1st, player_2nd, player_3rd, currentcard);
//
//    printf("Player %d is trying to show cards.\n", player_2nd.code);
//    if (player_2nd.code == 1) givingout_cards_sub_2_3(player_2nd, player_3rd, player_1st, currentcard);
//    if (player_2nd.code == 2 || player_2nd.code == 3) givingout_cards_sub_2_3(player_2nd, player_3rd, player_1st, currentcard);
//
//    printf("Player %d is trying to show cards.\n", player_3rd.code);
//    if (player_3rd.code == 1) givingout_cards_sub_2_3(player_3rd, player_1st, player_2nd, currentcard);
//    if (player_3rd.code == 2 || player_3rd.code == 3) givingout_cards_sub_2_3(player_3rd, player_1st, player_2nd, currentcard);
//
//    return 0;
//}
//
//int givingout_cards_sub_1(player player1, player playerx1, player playerx2, current currentcard) {
//    if (playerx1.cannotshow == 1 && playerx2.cannotshow == 1){
//        printf("You can give out cards in any combination.\n");
//        for (int i = 0; i <= player1.numofhand - 1; i++){
//            printf("[%d] %d %s\n", i+1, player1.hand[i].num, player1.hand[i].patt);
//        }
//        printf("Please give me your choice. (e.g. 1, 2, 3, 4)\n");
//        char* ans = calloc(60, sizeof(char));
//        scanf(ans);
//        player1 = aftershowing(player1, currentcard.cards);
//    }else{
//        printf("Do you have any combination larger than it?\n");
//        for (int i = 0; i <= player1.numofhand - 1; i++){
//            printf("[%d] %d %s\n", i+1, player1.hand[i].num, player1.hand[i].patt);
//        }
//        printf("Please give me your choice. (e.g. 1, 2, 3, 4)\n");
//
//        player1 = aftershowing(player1, currentcard.cards);
//    }
//    printcurrentcard(player1, currentcard.cards);
//    return 0;
//}
//
//int givingout_cards_sub_2_3(player player1, player playerx1, player playerx2, current currentcard){
//    if (playerx1.cannotshow == 1 && playerx2.cannotshow == 1){
//        currentcard = NPCshow_othernoshow(player1, currentcard);
//        player1 = aftershowing(player1, currentcard.cards);
//    }else{
//        currentcard = NPCshow(player1, currentcard);
//        player1 = aftershowing(player1, currentcard.cards);
//    }
//    printcurrentcard(player1, currentcard.cards);
//    return 0;
//}