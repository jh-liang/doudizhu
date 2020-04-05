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
const card triple_sample[3] = {
        {"diamond", 1, 1}, {"club", 1, 2}, {"heart", 1, 3}};
const card bomb_sample[4] = {
        {"diamond", 1, 1}, {"club", 1, 2}, {"heart", 1, 3},
        {"spade", 1, 4}};
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

    int *sequence = calloc(54, sizeof(int));
    for (int i = 0; i <= 53; i++) {
        sequence[i] = i;
    }
    for (int i = 0; i <= 53; i++) {             //弄一个sequence数组，用rand函数把sequence里的数字交换54次
        int a = rand() % 53;
        int X = sequence[a];
        sequence[a] = sequence[i];
        sequence[i] = X;
    }

    card *XX = calloc(54, sizeof(card));
    for (int i = 0; i <= 53; i++) {             //把sequence代入deck里面，shuffled = 洗好的牌
        XX[i] = deck[sequence[i]];
    }

    for (int i = 0; i <= 53; i++){
        deck[i] = XX[i];
    }

    free(XX);
    free(sequence);

    return deck;
}

player distributing(card* deck, player playerx, int playercode) {
    for (int i = 0; i <= 16; i++) {
        playerx.hand[i] = deck[i + (playercode - 1) * 13];
    }
    for (int i = 0; i <= 16; i++) {
        if (playerx.hand[i].code == 15) {playerx.role = "Load"; break;}
        else playerx.role = "Farmer";
    }
    for (int i = 17; i <= 19; i++) {
        playerx.hand[i].code = 0;
    }
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
    if (currentcard.special == 0){     //单牌、对子、三张、顺子、连对、飞机、三带二
        currentcard.cards = find(currentcard.cards, playerx.hand);
    }
    else{
        currentcard.cards = 0;
    }
    return currentcard;
}


current NPCshow_othernoshow(player playerx, current currentcard){
    int amount = countcard(playerx.hand);
    card* new = calloc(17, sizeof(card));

    new = findconst(tripair_sample, playerx.hand);
    if (new[0].num != 0) {currentcard.cards = new; return currentcard;}
    new = findconst(twotriple_sample, playerx.hand);
    if (new[0].num != 0) {currentcard.cards = new; return currentcard;}
    new = findconst(threetriple_sample, playerx.hand);
    if (new[0].num != 0) {currentcard.cards = new; return currentcard;}
    new = findconst(threeplustwo_sample_1, playerx.hand);
    if (new[0].num != 0) {currentcard.cards = new; return currentcard;}
    new = findconst(threeplustwo_sample_2, playerx.hand);
    if (new[0].num != 0) {currentcard.cards = new; return currentcard;}

    new = findconst(triple_sample, playerx.hand);
    if (new[0].num != 0) {currentcard.cards = new; return currentcard;}

    new = findconst(row_sample_12, playerx.hand);
    if (new[0].num != 0) {currentcard.cards = new; return currentcard;}

    new = findconst(row_sample_11, playerx.hand);
    if (new[0].num != 0) {currentcard.cards = new; return currentcard;}

    new = findconst(row_sample_10, playerx.hand);
    if (new[0].num != 0) {currentcard.cards = new; return currentcard;}

    new = findconst(row_sample_9, playerx.hand);
    if (new[0].num != 0) {currentcard.cards = new; return currentcard;}

    new = findconst(row_sample_8, playerx.hand);
    if (new[0].num != 0) {currentcard.cards = new; return currentcard;}

    new = findconst(row_sample_7, playerx.hand);
    if (new[0].num != 0) {currentcard.cards = new; return currentcard;}

    new = findconst(row_sample_6, playerx.hand);
    if (new[0].num != 0) {currentcard.cards = new; return currentcard;}

    new = findconst(row_sample_5, playerx.hand);
    if (new[0].num != 0) {currentcard.cards = new; return currentcard;}

    if (amount == 4) {
        new = findconst(bomb_sample, playerx.hand);
        if (new[0].num != 0) {
            currentcard.cards = new;
            return currentcard;
        }
    }

    if (amount == 6) {
        new = findconst(bombplustwo_sample, playerx.hand);
        if (new[0].num != 0) {currentcard.cards = new; return currentcard;}
        new = findconst(bombplustwo_sample_2, playerx.hand);
        if (new[0].num != 0) {currentcard.cards = new; return currentcard;}
        new = findconst(bombplustwo_sample_3, playerx.hand);
        if (new[0].num != 0) {currentcard.cards = new; return currentcard;}
        new = findconst(bombplustwo_sample_4, playerx.hand);
        if (new[0].num != 0) {currentcard.cards = new; return currentcard;}
    }



    for (int i = 0; i <= amount - 1; i++) {
        if (playerx.hand[i].num < 8 && playerx.hand[i].num != playerx.hand[i+1].num){
            new[0] = playerx.hand[i];
            break;
        }
        else if (playerx.hand[i].num < 8 && playerx.hand[i].num == playerx.hand[i+1].num){
            new[0] = playerx.hand[i];
            new[1] = playerx.hand[i + 1];
            break;
        }
        else if (playerx.hand[i].num < 8 && playerx.hand[i].num == playerx.hand[i+1].num
                && playerx.hand[i+1].num == playerx.hand[i+2].num){
            new[0] = playerx.hand[i];
            new[1] = playerx.hand[i + 1];
            new[2] = playerx.hand[i + 2];
            break;
        }
    }

    currentcard.cards = new;
    currentcard.special = 0;
    free(new);
    return currentcard;
}




player aftershowing(player playerx, card *currentcard) {
    int amount = countcard(currentcard);
    int pamount = countcard(playerx.hand);

    if (amount == 0) playerx.cannotshow = 1;
    else {
        for (int i = 0; i <= amount - 1; i++){
            for (int j = 0; j <= pamount - 1; j++){
                if (currentcard[i].code == playerx.hand[j].code){
                    for (int k = j; k <= (pamount-1); k++) {
                        playerx.hand[k] = playerx.hand[k + 1];
                    }
                    playerx.hand[pamount - 1].num = 0;
                    pamount--;
                    break;
                }
            }
        }
        playerx.numofhand -= amount;
        playerx.cannotshow = 0;
    }
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



card *find(card *currentcard, card *handcard){
    int amount = countcard(currentcard);
    int *pattern = calloc(amount, sizeof(int));
    for (int i = 0; i <= amount - 1; i++){
        pattern[i] = currentcard[i].num;
    }
    int *value = calloc(amount, sizeof(int));
    int *quatity = calloc(amount, sizeof(int));
    int hh = 0;
    for (int i = 0; i <= (amount - 1); i++){
        if (pattern[i] == pattern[i+1]){
            value[hh] = pattern[i];
            quatity[hh]++;
        }
        else hh++;                            //hh = len of value and quatity
    }

    int pamount = countcard(handcard);
    int *ppattern = calloc(pamount, sizeof(int));
    for (int i = 0; i <= pamount - 1; i++){
        ppattern[i] = handcard[i].num;
    }
    int *pvalue = calloc(pamount, sizeof(int));
    int *pquatity = calloc(pamount, sizeof(int));
    int phh = 0;
    for (int i = 0; i <= (pamount - 1); i++){
        if (ppattern[i] == ppattern[i+1]){
            pvalue[phh] = ppattern[i];
            pquatity[phh]++;
        }
        else phh++;                            //phh = len of pvalue and pquatity
    }

    int lhh = 0;
    int *lvalue = calloc(pamount, sizeof(int));
    int *lquatity = calloc(pamount, sizeof(int));
    for (int j = 0; j <= phh - 1; j++){
        if (pvalue[j] > value[0]){
            for (int k = 0; k <= (phh - j - 1); k++) {
                lquatity[k] = pquatity[j];
                lvalue[k] = pvalue[j];
            }
            lhh = phh - j;
            break;
        }
    }

    card *show = calloc(amount, sizeof(int));

    if (lhh < hh) {
        currentcard = show;
        free(show);
        free(pattern); free(quatity); free(value);
        free(ppattern); free(pquatity); free(pvalue);
        free(lquatity); free(lvalue);
        return currentcard;
    }

    int *dvalue = calloc(hh, sizeof(int));
    dvalue[0] = quatity[0];
    for (int i = 1; i <= hh - 1; i++) {
        dvalue[i] = quatity[i + 1] - quatity[i];
    }

    int *dlvalue = calloc(lhh, sizeof(int));
    dlvalue[0] = lquatity[0];
    for (int i = 1; i <= lhh - 1; i++) {
        dlvalue[i] = lquatity[i + 1] - lquatity[i];
    }


    int *new = calloc(amount, sizeof(int));
    int nhh = 0;

    for (int i = 1; i <= lhh - 1; i++){
        for (int j = 1; j <= hh - 1; j++){
            if (dlvalue[i + j] == dvalue[j] && quatity[i + j] <= pquatity[j] && quatity[i + j]+1 >= pquatity[j]){
                new[lhh] = value[i];
                nhh++;
            }
        }
        if (nhh == amount) break;
    }

    if (nhh != amount){
        free(pattern); free(quatity); free(value);
        free(ppattern); free(pquatity); free(pvalue);
        free(lquatity); free(lvalue);
        currentcard = show;
        free(show);
        free(dvalue); free(dlvalue); free(new);
        return currentcard;
    }


    for (int i = 0; i <= (amount-1); i++){
        for (int j = 0; j <= (pamount-1); j++) {
            if (handcard[j].num == new[i]) {
                show[i] = handcard[j];
                for (int k = j; k <= (pamount-1); k++) {
                    handcard[k] = handcard[k + 1];
                }
                pamount--;
                //printcurrentcard(playerx, currentcard);
                handcard[pamount-1].code = 0;
                break;
            }
        }
    }

    for (int i = nhh; i <= 19; i++) {
        show[i].code = 0;
        show[i].num = 0;
        show[i].patt = "diamond";
    }

    free(pattern); free(quatity); free(value);
    free(ppattern); free(pquatity); free(pvalue);
    free(lquatity); free(lvalue);
    currentcard = show;
    free(show);
    free(dvalue); free(dlvalue); free(new);
    return currentcard;
}








int printcurrentcard(player playerx, card *currentcard){
    int currentamount = countcard(currentcard);
    if (currentamount == 0)printf("Player %d cannot give out cards.", playerx.code);
    else {
        printf("Player %d gives out %d card(s). Current card is (are)", playerx.code, currentamount);
        for (int i = 0; i <= currentamount - 1; i++) {
            printf("[%d] %s %d", i + 1, currentcard[i].patt, currentcard[i].num);
        }
    }
    return 0;
}




card *findconst(const card sample[], card *handcard) {
    int amount = sizeof(sample)/sizeof(card);
    int *pattern = calloc(amount, sizeof(int));
    for (int i = 0; i <= amount - 1; i++){
        pattern[i] = sample[i].num;
    }
    int *value = calloc(amount, sizeof(int));
    int *quatity = calloc(amount, sizeof(int));
    int hh = 0;
    for (int i = 0; i <= (amount - 1); i++){
        if (pattern[i] == pattern[i+1]){
            value[hh] = pattern[i];
            quatity[hh]++;
        }
        else hh++;                            //hh = len of value and quatity
    }

    int pamount = countcard(handcard);
    int *ppattern = calloc(pamount, sizeof(int));
    for (int i = 0; i <= pamount - 1; i++){
        ppattern[i] = handcard[i].num;
    }
    int *pvalue = calloc(pamount, sizeof(int));
    int *pquatity = calloc(pamount, sizeof(int));
    int phh = 0;
    for (int i = 0; i <= (pamount - 1); i++){
        if (ppattern[i] == ppattern[i+1]){
            pvalue[phh] = ppattern[i];
            pquatity[phh]++;
        }
        else phh++;                            //phh = len of pvalue and pquatity
    }

    int lhh = 0;
    int *lvalue = calloc(pamount, sizeof(int));
    int *lquatity = calloc(pamount, sizeof(int));
    for (int j = 0; j <= phh - 1; j++){
        if (pvalue[j] > value[0]){
            for (int k = 0; k <= (phh - j - 1); k++) {
                lquatity[k] = pquatity[j];
                lvalue[k] = pvalue[j];
            }
            lhh = phh - j;
            break;
        }
    }

    card *show = calloc(amount, sizeof(int));

    if (lhh < hh) {
        handcard = show;
        free(show);
        free(pattern); free(quatity); free(value);
        free(ppattern); free(pquatity); free(pvalue);
        free(lquatity); free(lvalue);
        return handcard;
    }

    int *dvalue = calloc(hh, sizeof(int));
    dvalue[0] = quatity[0];
    for (int i = 1; i <= hh - 1; i++) {
        dvalue[i] = quatity[i + 1] - quatity[i];
    }

    int *dlvalue = calloc(lhh, sizeof(int));
    dlvalue[0] = lquatity[0];
    for (int i = 1; i <= lhh - 1; i++) {
        dlvalue[i] = lquatity[i + 1] - lquatity[i];
    }


    int *new = calloc(amount, sizeof(int));
    int nhh = 0;

    for (int i = 1; i <= lhh - 1; i++){
        for (int j = 1; j <= hh - 1; j++){
            if (dlvalue[i + j] == dvalue[j] && quatity[i + j] <= pquatity[j] && quatity[i + j]+1 >= pquatity[j]){
                new[lhh] = value[i];
                nhh++;
            }
        }
        if (nhh == amount) break;
    }

    if (nhh != amount){
        free(pattern); free(quatity); free(value);
        free(ppattern); free(pquatity); free(pvalue);
        free(lquatity); free(lvalue);
        handcard = show;
        free(show);
        free(dvalue); free(dlvalue); free(new);
        return handcard;
    }


    for (int i = 0; i <= (amount-1); i++){
        for (int j = 0; j <= (pamount-1); j++) {
            if (handcard[j].num == new[i]) {
                show[i] = handcard[j];
                for (int k = j; k <= (pamount-1); k++) {
                    handcard[k] = handcard[k + 1];
                }
                pamount--;
                //printcurrentcard(playerx, currentcard);
                handcard[pamount-1].code = 0;
                break;
            }
        }
    }

    for (int i = nhh; i <= 19; i++) {
        show[i].code = 0;
        show[i].num = 0;
        show[i].patt = "diamond";
    }

    free(pattern); free(quatity); free(value);
    free(ppattern); free(pquatity); free(pvalue);
    free(lquatity); free(lvalue);
    handcard = show;
    free(show);
    free(dvalue); free(dlvalue); free(new);
    return handcard;
}
