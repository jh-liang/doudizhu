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


    int b = rand() % 54;                        //根据斗地主规则，从牌组里抽一张牌出来，亮牌后放回牌组，派牌后拿到明牌的先交地主

    card shown = shuffled[b];

    for (int i = 0; i <= 16; i++) {
        player1.hand[i] = shuffled[i];
        if (i == b) {
            player1.role = "load";
            player2.role = "farmer";
            player3.role = "farmer";
        }
        player2.hand[i] = shuffled[i + 17];
        if (i == b) {
            player1.role = "farmer";
            player2.role = "load";
            player3.role = "farmer";
        }
        player3.hand[i] = shuffled[i + 34];
        if (i == b) {
            player1.role = "farmer";
            player2.role = "farmer";
            player3.role = "load";
        }
    }
    for (int i = 0; i <= 2; i++) {
        firstthree[i] = shuffled[i + 51];
    }
    ordering(17, player1.hand);             //排序各人的手牌
    ordering(17, player2.hand);
    ordering(17, player3.hand);
    ordering(3, firstthree);
    return 0;
}



int aftercallingload(player playerx, card firstthree[3]) {       //叫完地主后派地主牌
    playerx.hand[17] = firstthree[0];
    playerx.hand[18] = firstthree[1];
    playerx.hand[19] = firstthree[2];
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


int show(player playerx, card currentcard[13]) {         //出牌
    int currentamount;
    countcard(currentamount, currentcard);

    if (currentamount == 1) {           //单牌
        int cardcode = 0;
        for (cardcode = 0; cardcode <= 19; cardcode++) {
            if (playerx.hand[cardcode].num > currentcard[0].num) {
                break;
            }
        }
        if (cardcode < 20) {
            currentcard[0] = playerx.hand[cardcode];

            for (int i = 1; i <= 19; i++) {
                currentcard[i].patt = "nocard";
                currentcard[i].num = 0;
                currentcard[i].code = 0;
            }
            for (int i = cardcode; i <= playerx.numofhand; i++) {
                playerx.hand[cardcode] = playerx.hand[cardcode + 1];
            }
            printf("Player %d gives out a card. Current card is [1] %s %d", playerx.code, currentcard[0].patt,
                   currentcard[0].num);
            playerx.numofhand--;
            playerx.hand[playerx.numofhand].patt = "nocard";
            playerx.hand[playerx.numofhand].num = 0;
            playerx.hand[playerx.numofhand].code = 0;

        } else printf("Player %d cannot give out a card", playerx.code);
    } else if (currentamount == 2) {          //对子
        int cardcode = 0;
        for (cardcode = 0; cardcode <= 20; cardcode++) {
            if (playerx.hand[cardcode].num > currentcard[0].num &&
                playerx.hand[cardcode].num == playerx.hand[cardcode + 1].num) {
                break;
            }
        }
        if (cardcode < 19) {
            currentcard[0] = playerx.hand[cardcode];
            currentcard[1] = playerx.hand[cardcode + 1];
            printf("Player %d gives out a pair. Current card is [1] %s %d [2] %s %d", playerx.code,
                   currentcard[0].patt, currentcard[0].num, currentcard[1].patt, currentcard[1].num);
            playerx.numofhand = -2;
            for (int i = 2; i <= 19; i++) {
                currentcard[i].patt = "nocard";
                currentcard[i].num = 0;
                currentcard[i].code = 0;
            }
            for (int i = cardcode; i <= 19; i++) {
                playerx.hand[cardcode] = playerx.hand[cardcode + 2];
            }
            for (int i = playerx.numofhand; i <= playerx.numofhand + 2; i++) {
                playerx.hand[i].patt = "nocard";
                playerx.hand[i].num = 0;
                playerx.hand[i].code = 0;
            }
        } else printf("Player %d cannot give out a pair", playerx.code);
    } else if (currentamount == 3) {          //三张
        int cardcode = 0;
        for (cardcode = 0; cardcode <= 20; cardcode++) {
            if (playerx.hand[cardcode].num > currentcard[0].num &&
                playerx.hand[cardcode].num == playerx.hand[cardcode + 1].num
                && playerx.hand[cardcode + 1].num == playerx.hand[cardcode + 2].num) {
                break;
            }
        }
        if (cardcode < 18) {
            currentcard[0] = playerx.hand[cardcode];
            currentcard[1] = playerx.hand[cardcode + 1];
            currentcard[2] = playerx.hand[cardcode + 2];
            printf("Player %d gives out a tri. Current card is [1] %s %d [2] %s %d",
                   playerx.code, currentcard[0].patt, currentcard[0].num, currentcard[1].patt, currentcard[1].num);
            playerx.numofhand = -2;
            for (int i = 3; i <= 19; i++) {
                currentcard[i].patt = "nocard";
                currentcard[i].num = 0;
                currentcard[i].code = 0;
            }
            for (int i = cardcode; i <= 19; i++) {
                playerx.hand[cardcode]  = playerx.hand[cardcode + 3];
            }
            for (int i = playerx.numofhand; i <= playerx.numofhand + 3; i++) {
                playerx.hand[i].patt = "nocard";
                playerx.hand[i].num = 0;
                playerx.hand[i].code = 0;
            }

        } else printf("Player %d cannot give out a tri", playerx.code);
    } else if (currentamount == 6) {
        if (currentcard[0].num == currentcard[1].num && currentcard[1].num == currentcard[2].num + 1 &&
            currentcard[2].num == currentcard[3].num && currentcard[3].num == currentcard[4].num + 1 &&
            currentcard[4].num == currentcard[5].num) {          //连对
            int cardcode1 = 0;
            int cardcode2 = 0;
            int cardcode3 = 0;
            for (int i = 0; i <= 19; i++) {
                if (playerx.hand[i].num == playerx.hand[i + 1].num &&
                    playerx.hand[i - 2].num == playerx.hand[i - 1].num &&
                    playerx.hand[i].num == playerx.hand[i - 1].num + 1) {
                    cardcode2 = i;
                    cardcode1 = i - 2;

                    if (playerx.hand[i].num == playerx.hand[i + 1].num &&
                        playerx.hand[i + 2].num == playerx.hand[i + 3].num &&
                        playerx.hand[i].num == playerx.hand[i + 2].num - 1)
                        cardcode3 = i + 2;

                    if (playerx.hand[i].num == playerx.hand[i + 1].num &&
                        playerx.hand[i + 3].num == playerx.hand[i + 4].num &&
                        playerx.hand[i].num == playerx.hand[i + 3].num - 1)
                        cardcode3 = i + 3;
                };

                if (playerx.hand[i - 3].num == playerx.hand[i - 2].num &&
                    playerx.hand[i - 2].num == playerx.hand[i - 1].num &&
                    playerx.hand[i].num == playerx.hand[i + 1].num &&
                    playerx.hand[i + 1].num == playerx.hand[i + 2].num &&
                    playerx.hand[i + 3].num == playerx.hand[i + 4].num &&
                    playerx.hand[i + 4].num == playerx.hand[i + 5].num &&
                    playerx.hand[i - 1].num == playerx.hand[i].num - 1 &&
                    playerx.hand[i + 2].num == playerx.hand[i + 3].num - 1) {
                    cardcode3 = 0;
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
}


int countcard(int amount, card cards[20]) {              //数牌
    amount = 0;
    while (amount < 20) {
        if (cards[amount].patt != "nocard") amount++;
        else break;
    }
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
        else find(currentcard[i].num, handcode, position[i]);
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


int find(int target, int array[], int position) {            //找牌     //XXX 这里不确定能不能这样写
    for (int i = 0; i <= 19; i++) {
        if (target == array[i]) {
            position = i;
            break;
        }
    }
}