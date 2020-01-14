#include "stdio.h"
#include <math.h>
#include <stdlib.h>
#include "struct.h"
#include "function.h"


int main() {
    card deck[54];  //所有牌

    for (int i = 0; i <= 12; i++) {  //现在大小是1-13 没有AJQK 懒 以后再弄
        deck[i].num = i;
        deck[i].patt = "diamond";
        deck[i].code = i + 1;
    }
    for (int i = 13; i <= 25; i++) {
        deck[i - 13].num = i;
        deck[i - 13].patt = "club";
        deck[i].code = i + 1;
    }
    for (int i = 26; i <= 38; i++) {
        deck[i - 26].num = i;
        deck[i - 26].patt = "heart";
        deck[i].code = i + 1;
    }
    for (int i = 39; i <= 51; i++) {
        deck[i - 39].num = i;
        deck[i - 39].patt = "spade";
        deck[i].code = i + 1;
    }
    deck[52].code = 53;
    deck[52].num = 1;
    deck[52].patt = "joker";               //小王
    deck[53].code = 54;
    deck[53].num = 2;
    deck[53].patt = "joker";               //大王

    player player1;
    player1.code = 1;
    player player2;
    player2.code = 2;
    player player3;
    player3.code = 3;


    card firstthree[3];             //开局三张地主牌

    printf("shuffling...\n");
    shuffle(deck, player1, player2, player3, firstthree);   //洗牌
    //FIXME 把循环的判定条件重写一遍
    printf("Game Start.\nYour cards are as the following.\n");
    for (int i = 0; i <= 16; i++) printf("[%d] %s %d\n",i+1,player1.hand[i].patt, player1.hand[i].num);

    printf("The load cards are as the following.\n");
    for (int i = 0; i <= 2; i++) printf("[%d] %s %d\n", i+1,firstthree[i].patt, firstthree[i].num);

    int multiple = 1;       //倍数 用的是2的multiple次方

    if (player1.role == "load") {    //load = 地主
        printf("Do you want to be the load? Input your point! (0 - 2)");    //叫地主
        scanf("%d", &multiple);
        if (multiple == 0 && deck[1].num < 6) {
            printf("You don't want to be the load.\nPlayer 2 doesn't want to be the load.\nPlayer 3 wants to be the load.\nMultiple = %d.", 2^multiple);
            player1.role == "farmer.";
            player3.role == "load";
            aftercallingload(player3, firstthree);          //叫地主后的给牌程序
        } else if (multiple == 0 && deck[1].num >= 6) {
            multiple = 2;
            printf("You don't want to be the load.\nPlayer 2 wants to be the load.\n Multiple = %d.\nPlayer 3 doesn't want to be the load.", 2^multiple);
            player1.role == "farmer.";
            player2.role == "load";
            aftercallingload(player2, firstthree);
        } else {
            printf("You want to be the load.\nPlayer 2 doesn't want to be the load.\nPlayer 3 doesn't want to be the load.\n Multiple = %d.",
                   2 ^ multiple);
            aftercallingload(player1, firstthree);
        }
    } else {
        if (player2.role == "load") {
            printf("Player2 wants to be the load. Multiple = %d.\nPlayer 3 doesn't want to be the load.\nDo you want to be the load? [Y/N]", 2^multiple);
            char c;
            scanf("%c", c);
            if (c == 'Y' || c == 'y') {
                multiple++;
                player1.role = "load";
                player2.role = "farmer";
                printf("Multiple = %d.\nYou are the load now.", 2^multiple);
                aftercallingload(player1, firstthree);
            } else {
                printf("Player2 is the load now!");
                aftercallingload(player2, firstthree);
            }
        }
        if (player3.role == "load") {
            printf("Player3 want to be the load. Multiple = %d.\nDo you want to be the load? [Y/N]", 2^multiple);
            char c;
            scanf("%c", c);
            if (c == 'Y') {
                multiple++;
                player1.role = "load";
                player3.role = "farmer";
                printf("Multiple = %d.\nPlayer2 doesn't want to be the load.\nYou are the load now.", 2^multiple);
                aftercallingload(player1, firstthree);
            } else {
                printf("Player1 don't want to be the load.\nPlayer2 doesn't want to be the load.\nPlayer3 is the load now!");
                aftercallingload(player3, firstthree);
            }
        }
    }

        card currentcard[13];                   //牌桌上现在的牌组
        for (int i = 0; i <= 12; i++){
            currentcard[i].patt = "nocard";
            currentcard[i].num = 0;
            currentcard[i].code = 0;
        }




        return 0;
}
