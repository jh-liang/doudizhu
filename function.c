//
// Created by zxj on 2020/1/14.
//

#include "function.h"



card* shuffle(card *deck) {     //开局洗牌
    for (int j = 0; j <= 3 ; j++){            //现在大小是1-13 没有AJQK 懒 以后再弄
        for (int i = 0; i <= 12; i++) {
            deck[i + j*13].num = i;
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
    deck[52].num = 1;
    deck[52].patt = "joker";               //小王
    deck[53].code = 54;
    deck[53].num = 2;
    deck[53].patt = "joker";               //大王



    int sequence[54];
    for (int i = 0; i <= 53; i++) {
        sequence[i] = i;
    }
    for (int i = 0; i <= 53; i++) {             //弄一个sequence数组，用rand函数把sequence里的数字交换54次
        int a = rand() % 53;
        int X = sequence[a];
        sequence[a] = sequence[i];
        sequence[i] = X;
    }

    for (int i = 0; i <= 53; i++) {             //把sequence代入deck里面，shuffled = 洗好的牌
        deck[i] = deck[sequence[i]];        //这里应该洗好牌了
    }
}

player distributing(card *deck, player playerx, int playercode) {
    for (int i = 0; i <= 16; i++) {
        playerx.hand[i] = deck[i + (playercode - 1) * 13];
        if (playerx.hand[i].code == 15) playerx.role = "Load";
        else playerx.role = "Farmer";
    }
    for (int i = 17; i <= 19; i++) {
        playerx.hand[i].code = 0;
    }
    playerx.hand = ordering(playerx.hand);
    return playerx;
}

card* shufflethefirstthree(card *deck, card firstthree[3]){
    for (int i = 0; i <= 2; i++) {
        firstthree[i] = deck[i + 51];
    }
    firstthree = ordering(firstthree);
    return firstthree;
}



player aftercallingload(player playerx, card firstthree[3]) {       //叫完地主后派地主牌
    playerx.hand[17] = firstthree[0];
    playerx.hand[18] = firstthree[1];
    playerx.hand[19] = firstthree[2];
    playerx.numofhand+=3;
    return playerx;
}

//FIXME: 改循环的判定条件，上面已经帮你改过几个了
card* ordering(card *cards){           //排序牌组
    int amount = countcard(cards);
    for (int j = amount - 1; j >= 0; j--) {  // 我不知道这边写的什么jb，第二个语句是循环执行条件，写成这样根本没法循环，后面也有好多
        card a = cards[0];                      //ljh:记错了 记成第二句是结束条件了。。。
        int a1 = 0;
        for (int i = 0; i <= j; i++) {   // 一样的问题
            if (cards[i].num < cards[i + 1].num){
                a = cards[i + 1];
                a1 = i + 1;
            }
        }
        card cardsx = cards[j];
        cards[a1] = cards[j];
        cards[j] = cardsx;
    }
    return cards;
}


card* NPCshow(player playerx, card *currentcard){
    int currentamount = countcard(currentcard);
    if (currentamount == 1) {           //单牌
        int cardcode = 0;
        for (cardcode = 0; cardcode <= 19; cardcode++) {
            if (playerx.hand[cardcode].num > currentcard[0].num &&
                playerx.hand[cardcode].num != playerx.hand[cardcode+1].num)
                break;
        }
        if (cardcode < 20) {
                currentcard[0] = playerx.hand[cardcode];
                for (int i = 1; i <= 19; i++) {
                    currentcard[i].code = 0;
                }
                playerx.numofhand--;
                for (int i = cardcode; i <= playerx.numofhand - 1; i++) {
                    playerx.hand[i] = playerx.hand[i + 1];
                }
                printcurrentcard(playerx, currentcard);
                playerx.hand[playerx.numofhand].code = 0;

                othernoshow = 0;
        }
        else{
            printf("Player %d cannot give out a card", playerx.code);
            othernoshow++;
        }
    }
    else if (currentamount == 2){          //对子
        int cardcode = 0;
        for (cardcode = 0; cardcode <= 20; cardcode++) {
            if (playerx.hand[cardcode].num > currentcard[0].num &&
                playerx.hand[cardcode].num == playerx.hand[cardcode + 1].num &&
                playerx.hand[cardcode + 1].num != playerx.hand[cardcode + 2].num)
                break;
        }
        if (cardcode < 20) {
            currentcard[0] = playerx.hand[cardcode];
            currentcard[1] = playerx.hand[cardcode + 1];
            for (int i = 2; i <= 19; i++) {
                currentcard[i].code = 0;
            }
            playerx.numofhand -= 2;
            for (int i = cardcode; i <= playerx.numofhand -1; i++) {
                playerx.hand[cardcode] = playerx.hand[cardcode + 2];
            }
            printcurrentcard(playerx, currentcard);
            playerx.hand[playerx.numofhand].code = 0;
            playerx.hand[playerx.numofhand + 1].code = 0;
            othernoshow = 0;
        }
        else{
            printf("Player %d cannot give out a pair", playerx.code);
            playerx.hand[playerx.numofhand].code = 0;
        }
    }
    else if (currentamount == 3){          //三张
        int cardcode = 0;
        for (cardcode = 0; cardcode <= 20; cardcode++) {
            if (playerx.hand[cardcode].num > currentcard[0].num
                && playerx.hand[cardcode].num == playerx.hand[cardcode + 1].num
                && playerx.hand[cardcode + 1].num == playerx.hand[cardcode + 2].num
                && playerx.hand[cardcode + 2].num != playerx.hand[cardcode + 3].num)
                break;
        }
        if (cardcode < 20) {
            currentcard[0] = playerx.hand[cardcode];
            currentcard[1] = playerx.hand[cardcode + 1];
            currentcard[2] = playerx.hand[cardcode + 2];
            for (int i = 3; i <= 19; i++) {
                currentcard[i].code = 0;
            }
            playerx.numofhand-=3;
            printcurrentcard(playerx, currentcard);
            for (int i = playerx.numofhand; i <= playerx.numofhand + 2; i++) {
                playerx.hand[i].code = 0;
            }
            othernoshow = 0;
        }
        else{
            printf("Player %d cannot give out a tri", playerx.code);
            othernoshow++;
        }
    }
    else if(currentamount == 6){
        if (currentcard[0].num == currentcard[1].num && currentcard[1].num == currentcard[2].num + 1 &&
            currentcard[2].num == currentcard[3].num && currentcard[3].num == currentcard[4].num + 1 &&
            currentcard[4].num == currentcard[5].num){          //连对
            int cardcode1 = 0;
            int cardcode2 = 0;
            int cardcode3 = 0;
            for (int i = 0; i <= 19; i++) {
                if (playerx.hand[i].num == playerx.hand[i + 1].num && playerx.hand[i + 2].num == playerx.hand[i + 3].num
                    && playerx.hand[i + 4].num == playerx.hand[i + 5].num && playerx.hand[i + 1].num == playerx.hand[i + 2].num + 1
                    && playerx.hand[i + 3].num == playerx.hand[i + 4].num + 1){
                    cardcode1 = i; cardcode2 = i+2; cardcode3 = i+4; break;
                }
                if (playerx.hand[i].num == playerx.hand[i + 1].num && playerx.hand[i + 1].num == playerx.hand[i + 2].num
                    && playerx.hand[i + 3].num == playerx.hand[i + 4].num && playerx.hand[i + 5].num == playerx.hand[i + 6].num 
                    && playerx.hand[i + 2].num == playerx.hand[i + 3].num + 1 &&
                    playerx.hand[i + 3].num == playerx.hand[i + 4].num + 1){
                    cardcode1 = i; cardcode2 = i+2; cardcode3 = i+4; break;
                }
                if (playerx.hand[i].num == playerx.hand[i + 1].num && playerx.hand[i].num == playerx.hand[i + 1].num &&
                    playerx.hand[i + 2].num == playerx.hand[i + 3].num &&
                    playerx.hand[i + 4].num == playerx.hand[i + 5].num &&
                    playerx.hand[i + 1].num == playerx.hand[i + 2].num + 1 &&
                    playerx.hand[i + 3].num == playerx.hand[i + 4].num + 1){
                    cardcode1 = i; cardcode2 = i+2; cardcode3 = i+4; break;
                }
                if (playerx.hand[i].num == playerx.hand[i + 1].num && playerx.hand[i].num == playerx.hand[i + 1].num &&
                    playerx.hand[i + 2].num == playerx.hand[i + 3].num &&
                    playerx.hand[i + 4].num == playerx.hand[i + 5].num &&
                    playerx.hand[i + 1].num == playerx.hand[i + 2].num + 1 &&
                    playerx.hand[i + 3].num == playerx.hand[i + 4].num + 1){
                    cardcode1 = i; cardcode2 = i+2; cardcode3 = i+4; break;
                }
            }
            if (cardcode3 != 0) {
                currentcard[0] = playerx.hand[cardcode1];
                currentcard[1] = playerx.hand[cardcode1 + 1];
                currentcard[2] = playerx.hand[cardcode2];
                currentcard[3] = playerx.hand[cardcode2 + 1];
                currentcard[4] = playerx.hand[cardcode3];
                currentcard[5] = playerx.hand[cardcode3 + 1];
                printf("Player %d gives out a tri-pair. Current card is [1] %s %d\n[2] %s %d\n[3] %s %d\n[4] %s %d\n[5] %s %d\n[6] %s %d\n",
                       playerx.code, currentcard[0].patt, currentcard[0].num, currentcard[1].patt,
                       currentcard[1].num, currentcard[2].patt, currentcard[2].num,
                       currentcard[3].patt, currentcard[3].num, currentcard[4].patt, currentcard[4].num,
                       currentcard[5].patt, currentcard[5].num);
                playerx.numofhand = -6;
                for (int i = 6; i <= 19; i++) {
                    currentcard[i].patt = "nocard";
                    currentcard[i].num = 0;
                    currentcard[i].code = 0;
                }
                for (int i = cardcode1; i <= cardcode2; i++) {
                    playerx.hand[cardcode1] = playerx.hand[cardcode1 + 2];
                }
                for (int i = cardcode2; i <= cardcode3; i++) {
                    playerx.hand[cardcode2] = playerx.hand[cardcode2 + 4];
                }
                for (int i = cardcode3; i <= 19; i++) {
                    playerx.hand[cardcode3] = playerx.hand[cardcode3 + 6];
                }
            } else printf("Player %d cannot give out a tri-pair", playerx.code);
        } else if (currentcard[0].num == currentcard[1].num && currentcard[3].num == currentcard[4].num &&
                   currentcard[1].num == currentcard[2].num && currentcard[4].num == currentcard[5].num &&
                   currentcard[2].num == currentcard[3].num + 1) {
            int cardcode1 = 0;
            int cardcode2 = 0;
            for (int i = 0; i <= 19; i++){
                if (playerx.hand[i].num == playerx.hand[i+1].num && playerx.hand[i+1].num == playerx.hand[i+2].num &&
                    playerx.hand[i+3].num == playerx.hand[i+4].num && playerx.hand[i+4].num == playerx.hand[i+5].num &&
                    playerx.hand[i+2].num == playerx.hand[i+3].num - 1 && playerx.hand[i+5].num != playerx.hand[i+6].num){
                    cardcode1 = i;
                    cardcode2 = i+3;
                }
            }


        }


    }else wannengrow(playerx, currentcard, currentamount);
    return currentcard;
}


int countcard(card *cards) {              //数牌
    int amount = 0;
    while (amount < 20) {
        if (cards[amount].num != 0) amount++;
        else break;
    }
    return amount;
}


int wannengrow(player playerx, card currentcard[13], int currentamount) {        //顺子
    int handamount;
    int handcode[handamount];
    for (int i = 0; i <= handamount; i++) {
        handcode[i] = playerx.hand[i].num;
    }

    int currentarray[currentamount];
    int position[currentamount];                    //position是在array里面的坐标，第一个=0

    for (int i = 0; i <= currentamount; i++) {
        if (position[i] != 0) continue;
        else position[i] = findpos(currentcard[i].num, handcode);
    }

    int foundindicator = 1;

    for (int i = 0; i <= currentamount; i++) {
        if (position[i] == 0){
            foundindicator = 0;
            break;
        }
    }

    if (foundindicator == 1) {
        for (int i = 0; i <= currentamount; i++) {
            currentcard[i] = playerx.hand[position[i]];
        }
        printf("Player %d gives out a row. Current card is\n", playerx.code);
        for (int i = 0; i <= currentamount; i++) {
            printf("[%d] %s %d\n", currentcard[0].patt, currentcard[0].num);
        }
        playerx.numofhand = -currentamount;

        for (int i = currentamount; i <= 19; i++) {
            currentcard[i].patt = "nocard";
            currentcard[i].num = 0;
            currentcard[i].code = 0;
        }
        for (int i = 0; i <= currentamount; i++) {
            for (int j = position[i]; j <= position[i + 1]; j++) {
                playerx.hand[j] = playerx.hand[j + i + 1];
            }
        }
    } else printf("Player %d cannot give out a role", playerx.code);


}


int findpos(int target, int cardarray[]) {            //找牌     //XXX 这里不确定能不能这样写
    int position;
    for (int i = 0; i <= 19; i++) {
        if (target == cardarray[i]) {
            position = i;
            break;
        }
    }
    return position;
}


card *find(card *currentcard, card *handcard){
    int amount = countcard(currentcard);
    int *pattern = {0};
    for (int i = 0; i <= amount - 1; i++){
        pattern[i] = currentcard[i].num;
    }
    int *value = {0};
    int *quatity = {0};
    int hh = 0;
    for (int i = 0; i <= (amount - 1); i++){
        if (pattern[i] == pattern[i+1]){
            value[hh] = pattern[i];
            quatity[hh]++;
        }
        else hh++;                            //hh = len of value and quatity
    }

    int pamount;
    pamount = countcard(handcard);
    int ppattern[] = {0};
    for (int i = 0; i <= pamount - 1; i++){
        ppattern[i] = handcard[i].num;
    }
    int pvalue[] = {0};
    int pquatity[] = {0};
    int phh = 0;
    for (int i = 0; i <= (pamount - 1); i++){
        if (ppattern[i] == ppattern[i+1]){
            pvalue[phh] = ppattern[i];
            pquatity[phh]++;
        }
        else phh++;                            //phh = len of pvalue and pquatity
    }

    int lhh = 0;
    int *lvalue;
    int *lquatity;
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

    card *show = {0};

    if (lhh < hh) return show;

    int *dvalue;
    dvalue[0] = quatity[0];
    for (int i = 1; i <= hh - 1; i++) {
        dvalue[i] = quatity[i + 1] - quatity[i];
    }

    int *dlvalue;
    dlvalue[0] = lquatity[0];
    for (int i = 1; i <= lhh - 1; i++) {
        dlvalue[i] = lquatity[i + 1] - lquatity[i];
    }


    int *new = {0};
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

    if (nhh != amount) return show;


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
                //othernoshow = 0;
                break;
            }
        }
    }

    for (int i = nhh; i <= 19; i++) {
        show[i].code = 0;
        show[i].num = 0;
        show[i].patt = "diamond";
    }

    return show;
}








int printcurrentcard(player playerx, card *currentcard){
    int currentamount = countcard(currentcard);
    printf("Player %d gives out %d card(s). Current card is (are)", playerx.code, currentamount);
    for (int i = 0; i <= currentamount - 1; i++){
        printf("[%d] %s %d", i+1, currentcard[i].patt, currentcard[i].num);
    }
    return 0;
}
