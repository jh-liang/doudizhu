//
// Created by zxj on 2020/1/14.
//

#include "function.h"



int shuffle(card *deck, player player1, player player2, player player3, card *firstthree) {     //开局洗牌
    player1.numofhand = 17;
    player2.numofhand = 17;
    player3.numofhand = 17;

    card shuffled[54];      //要洗的牌

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
        shuffled[i] = deck[sequence[i]];        //这里应该洗好牌了
    }


    int b = rand() % 54;                        //根据斗地主规则，从牌组里抽一张牌出来，亮牌后放回牌组，派牌后拿到明牌的先叫地主

    card shown = shuffled[b];

    for (int i = 0; i <= 16; i++) {
        player1.hand[i] = shuffled[i];
        player2.hand[i] = shuffled[i + 17];
        player3.hand[i] = shuffled[i + 34];
        if (i == b) {
            player1.role = "load"; player2.role = "farmer"; player3.role = "farmer";
        }
        if ((i+17) == b) {
            player1.role = "farmer"; player2.role = "load"; player3.role = "farmer";
        }
        if ((i+34) == b) {
            player1.role = "farmer"; player2.role = "farmer"; player3.role = "load";
        }
    }
    for (int i = 0; i <= 2; i++) {
        firstthree[i] = shuffled[i + 51];
    }
    for (int i = 17; i <= 19; i++) {
        player1.hand[i].code = 0;
        player2.hand[i].code = 0;
        player3.hand[i].code = 0;
    }
    ordering(countcard(player1.hand), player1.hand);             //排序各人的手牌
    ordering(countcard(player2.hand), player2.hand);
    ordering(countcard(player3.hand), player3.hand);
    ordering(3, firstthree);
    return 0;
}



int aftercallingload(player playerx, card firstthree[3]) {       //叫完地主后派地主牌
    playerx.hand[17] = firstthree[0];
    playerx.hand[18] = firstthree[1];
    playerx.hand[19] = firstthree[2];
    playerx.numofhand+=3;
    return 0;
}

//FIXME: 改循环的判定条件，上面已经帮你改过几个了
int ordering(int amount, card cards[amount]) {           //排序牌组
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
}


int NPCshow(player playerx, card currentcard[13], int othernoshow){ 
    int currentamount = countcard(currentcard);

    if (othernoshow == 2){

    }

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
            };
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
}


int countcard(card cards[20]) {              //数牌
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
        else findpos(currentcard[i].num, handcode, position[i]);
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


int findpos(int target, int cardarray[], int position) {            //找牌     //XXX 这里不确定能不能这样写
    for (int i = 0; i <= 19; i++) {
        if (target == cardarray[i]) {
            position = i;
            break;
        }
    }
}


int findpos(card target[20], card prey[20]){
    int amount;
    amount = countcard(target);
    int pattern[] = {0};
    for (int i = 0; i <= amount - 1; i++){
        pattern[i] = target[i].num;
    }
    int value[] = {0};
    int quatity[] = {0};
    int hh = 0;
    for (int i = 0; i <= (amount - 1); i++){
        if (pattern[i] == pattern[i+1]){
            value[hh] = pattern[i];
            quatity[hh]++;
        }
        else hh++;
    }

    int pamount;
    pamount = countcard(prey);
    int ppattern[] = {0};
    for (int i = 0; i <= pamount - 1; i++){
        ppattern[i] = prey[i].num;
    }
    int pvalue[] = {0};
    int pquatity[] = {0};
    int phh = 0;
    for (int i = 0; i <= (pamount - 1); i++){
        if (ppattern[i] == ppattern[i+1]){
            pvalue[phh] = ppattern[i];
            pquatity[phh]++;
        }
        else phh++;
    }

    int new[];

    for (int i = 0; i <= hh - 1; i++){
        for (int j = 0; j <= phh - 1; j++){
            


        }


    }


    return 0;
}








int printcurrentcard(player playerx, card currentcard[13]){
    int currentamount = countcard(currentcard);
    printf("Player %d gives out %d card(s). Current card is (are)", playerx.code, currentamount);
    for (int i = 0; i <= currentamount - 1; i++){
        printf("[%d] %s %d", i+1, currentcard[i].patt, currentcard[i].num);
    }
    return 0;
}
