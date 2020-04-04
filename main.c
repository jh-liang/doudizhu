#include "stdio.h"
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include "struct.h"
#include "function.h"


int main() {
    card *deck;  //所有牌

    player player1;
    player1.code = 1;
    player1.numofhand = 17;
    player1.cannotshow = 0;
    player player2;
    player2.code = 2;
    player2.numofhand = 17;
    player2.cannotshow = 0;
    player player3;
    player3.code = 3;
    player3.numofhand = 17;
    player3.cannotshow = 0;

    card *firstthree;             //开局三张地主牌
    printf("shuffling...\n");
    deck = shuffle(deck);   //洗牌
    player1 = distributing(deck, player1, 1);
    player2 = distributing(deck, player2, 2);
    player3 = distributing(deck, player3, 3);
    firstthree = shufflethefirstthree(deck, firstthree);

    //FIXME 把循环的判定条件重写一遍
    printf("Game Start.\nYour cards are as the following.\n");
    for (int i = 0; i <= 16; i++) printf("[%d] %s %d\n", i + 1, player1.hand[i].patt, player1.hand[i].num);

    printf("The Load cards are as the following.\n");
    for (int i = 0; i <= 2; i++) printf("[%d] %s %d\n", i + 1, firstthree[i].patt, firstthree[i].num);

    int multiple = 0;       //倍数 用的是2的multiple次方

    if (strncmp(player1.role, "Load", 4) == 0) {    //Load = 地主
        printf("Do you want to be the Load? Input your point! (0 - 2)");    //叫地主
        scanf("%d", &multiple);
        if (multiple == 0 && deck[1].num < 6) {
            printf("You don't want to be the Load.\nPlayer 2 doesn't want to be the Load.\nPlayer 3 wants to be the Load.\nMultiple = %f.",
                   pow(2, multiple));
            player1.role = "farmer.";
            player3.role = "Load";
            player3 = aftercallingload(player3, firstthree);          //叫地主后的给牌程序
        } else if (multiple == 0 && deck[1].num >= 6) {
            multiple = 2;
            printf("You don't want to be the Load.\nPlayer 2 wants to be the Load.\n Multiple = %f.\nPlayer 3 doesn't want to be the Load.",
                   pow(2, multiple));
            player1.role = "farmer.";
            player2.role = "Load";
            player2 = aftercallingload(player2, firstthree);
        } else {
            printf("You want to be the Load.\nPlayer 2 doesn't want to be the Load.\nPlayer 3 doesn't want to be the Load.\n Multiple = %f.",
                   pow(2, multiple));
            player1 = aftercallingload(player1, firstthree);
        }
    } else {
        if (strncmp(player2.role, "Load", 4) == 0) {
            multiple++;
            printf("Player2 wants to be the Load. Multiple = %f.\nPlayer 3 doesn't want to be the Load.\nDo you want to be the Load? [Y/N]",
                   pow(2, multiple));
            char c;
            scanf("%c", &c);
            if (c == 'Y' || c == 'y') {
                player1.role = "Load";
                player2.role = "farmer";
                multiple++;
                printf("Multiple = %f.\nYou are the Load now.", pow(2, multiple));
                player1 = aftercallingload(player1, firstthree);
            } else {
                printf("Player2 is the Load now!");
                player2 = aftercallingload(player2, firstthree);
            }
        }
        if (strncmp(player3.role, "Load", 4) == 0) {
            multiple++;
            printf("Player3 want to be the Load. Multiple = %f.\nDo you want to be the Load? [Y/N]", pow(2, multiple));
            char c;
            scanf("%c", &c);
            if (c == 'Y') {
                multiple++;
                player1.role = "Load";
                player3.role = "farmer";
                printf("Multiple = %f.\nPlayer2 doesn't want to be the Load.\nYou are the Load now.", pow(2, multiple));
                player1 = aftercallingload(player1, firstthree);
            } else {
                printf("Player1 don't want to be the Load.\nPlayer2 doesn't want to be the Load.\nPlayer3 is the Load now!");
                player3 = aftercallingload(player3, firstthree);
            }
        }
    }

    card *currentcard = {0};                   //牌桌上现在的牌组

    while (player1.numofhand > 0 || player2.numofhand > 0 || player3.numofhand > 0) {
        if (strncmp(player1.role, "Load", 4) == 0){
            printf("Player 1 is trying to show cards.");
            if (player2.cannotshow == 1 && player3.cannotshow == 1){

            }else{

            }
            if (currentcard[0].num == 0) printf("Player 1 cannot show his cards.");
            else printcurrentcard(player1, currentcard);


            printf("Player 2 is trying to show cards.");
            if (player1.cannotshow == 1 && player3.cannotshow == 1){

            }else{
                currentcard = NPCshow(player2, currentcard);
            }
            if (currentcard[0].num == 0) printf("Player 2 cannot show his cards.");
            else printcurrentcard(player2, currentcard);


            printf("Player 3 is trying to show cards.");
            if (player1.cannotshow == 1 && player2.cannotshow == 1){

            }else{
                currentcard = NPCshow(player3, currentcard);
            }
            if (currentcard[0].num == 0) printf("Player 3 cannot show his cards.");
            else printcurrentcard(player3, currentcard);
        }

        else if (strncmp(player2.role, "Load", 4) == 0){
            printf("Player 2 is trying to show cards.");
            if (player1.cannotshow == 1 && player3.cannotshow == 1){

            }else{
                currentcard = NPCshow(player2, currentcard);
            }
            if (currentcard[0].num == 0) printf("Player 2 cannot show his cards.");
            else printcurrentcard(player2, currentcard);


            printf("Player 3 is trying to show cards.");
            if (player1.cannotshow == 1 && player2.cannotshow == 1){

            }else{
                currentcard = NPCshow(player3, currentcard);
            }
            if (currentcard[0].num == 0) printf("Player 3 cannot show his cards.");
            else printcurrentcard(player3, currentcard);


            printf("Player 1 is trying to show cards.");
            if (player2.cannotshow == 1 && player3.cannotshow == 1){

            }else{

            }
            if (currentcard[0].num == 0) printf("Player 1 cannot show his cards.");
            else printcurrentcard(player1, currentcard);
        }
        else{
            printf("Player 3 is trying to show cards.");
            if (player1.cannotshow == 1 && player2.cannotshow == 1){

            }else{
                currentcard = NPCshow(player3, currentcard);
            }
            if (currentcard[0].num == 0) printf("Player 3 cannot show his cards.");
            else printcurrentcard(player3, currentcard);

            printf("Player 1 is trying to show cards.");
            if (player2.cannotshow == 1 && player3.cannotshow == 1){

            }else{

            }
            if (currentcard[0].num == 0) printf("Player 1 cannot show his cards.");
            else printcurrentcard(player1, currentcard);

            printf("Player 2 is trying to show cards.");
            if (player3.cannotshow == 1 && player1.cannotshow == 1){

            }else{
                currentcard = NPCshow(player2, currentcard);
            }
            if (currentcard[0].num == 0) printf("Player 2 cannot show his cards.");
            else printcurrentcard(player2, currentcard);
        }


    }





    if (player1.numofhand == 0){
        if (strncmp(player1.role, "Load", 4) == 0){
            printf("Player 1 wins!");
        }
        else if (strncmp(player2.role, "Load", 4) == 0){
            printf("Player 1 wins!");
            printf("Player 3 wins!");
        }
        else{
            printf("Player 1 wins!");
            printf("Player 2 wins!");
        }
    }
    if (player2.numofhand == 0){
        if (strncmp(player2.role, "Load", 4) == 0){
            printf("Player 2 wins!");
        }
        else if (strncmp(player3.role, "Load", 4) == 0){
            printf("Player 1 wins!");
            printf("Player 2 wins!");
        }
        else{
            printf("Player 2 wins!");
            printf("Player 3 wins!");
        }
    }
    if (player3.numofhand == 0){
        if (strncmp(player3.role, "Load", 4) == 0){
            printf("Player 3 wins!");
        }
        else if (strncmp(player1.role, "Load", 4) == 0){
            printf("Player 2 wins!");
            printf("Player 3 wins!");
        }
        else{
            printf("Player 1 wins!");
            printf("Player 3 wins!");
        }
    }

    printf("Game End!");
    return 0;
}
