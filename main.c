#include "function.h"

int main() {
    card *deck = calloc(54, sizeof(card));  //所有牌

    player player1 = {"", calloc(20, sizeof(card)),17, 1, 1};
    player player2 = {"", calloc(20, sizeof(card)),17, 2, 1};
    player player3 = {"", calloc(20, sizeof(card)),17, 3, 1};

    card *firstthree = calloc(54, sizeof(card));             //开局三张地主牌
    printf("shuffling...\n");
    deck = shuffle(deck);   //洗牌
    player1 = distributing(deck, player1);
    player2 = distributing(deck, player2);
    player3 = distributing(deck, player3);
    firstthree = shufflethefirstthree(deck, firstthree);
    free(deck);

    //FIXME 把循环的判定条件重写一遍
    printf("Game Start.\nYour cards are as the following.\n");
    for (int i = 0; i <= 16; i++) printf("[%d] %s %d\n", i + 1, player1.hand[i].patt, player1.hand[i].num);

    printf("The Load cards are as the following.\n");
    for (int i = 0; i <= 2; i++) printf("[%d] %s %d\n", i + 1, firstthree[i].patt, firstthree[i].num);

    current currentcard = {calloc(20, sizeof(card)), 0, 0, 0};                 //牌桌上现在的牌组
    

    if (strncmp(player1.role, "Load", 4) == 0) {    //Load = 地主
        printf("Do you want to be the Load? Input your point! (0 - 2)");    //叫地主
        scanf("%d", &currentcard.multiple);
        if ( currentcard.multiple == 0 && player1.hand[7].num < 6) {
            printf("You don't want to be the Load.\nPlayer 2 doesn't want to be the Load.\nPlayer 3 wants to be the Load.\nMultiple = %f.\nPlayer 3 is the Load now.\n",
                   pow(2,  currentcard.multiple));
            player1.role = "Farmer.";
            player3.role = "Load";
            player3 = aftercallingload(player3, firstthree);          //叫地主后的给牌程序
            memset(player1.hand+17, 0, 3 * sizeof(card));
            memset(player2.hand+17, 0, 3 * sizeof(card));
        } else if ( currentcard.multiple == 0 && player1.hand[7].num >= 6) {
             currentcard.multiple = 2;
            printf("You don't want to be the Load.\nPlayer 2 wants to be the Load.\nPlayer 3 doesn't want to be the Load.\nMultiple = %f.\nPlayer 2 is the Load now.\n",
                   pow(2,  currentcard.multiple));
            player1.role = "Farmer.";
            player2.role = "Load";
            player2 = aftercallingload(player2, firstthree);
            memset(player1.hand+17, 0, 3 * sizeof(card));
            memset(player3.hand+17, 0, 3 * sizeof(card));
        } else {
            printf("You want to be the Load.\nPlayer 2 doesn't want to be the Load.\nPlayer 3 doesn't want to be the Load.\nMultiple = %f.\nYou are the Load now.\n",
                    pow(2,  currentcard.multiple));
            player1 = aftercallingload(player1, firstthree);
            memset(player2.hand+17, 0, 3 * sizeof(card));
            memset(player3.hand+17, 0, 3 * sizeof(card));
        }
    }
    else if (strncmp(player2.role, "Load", 4) == 0) {
        currentcard.multiple = 1;
        printf("Player2 wants to be the Load.\nMultiple = %f.\nPlayer 3 doesn't want to be the Load.\nDo you want to be the Load? [Y/N]",
               pow(2,  currentcard.multiple));
        char c;
        scanf("%c", &c);
        if (c == 'Y' || c == 'y') {
            player1.role = "Load";
            player2.role = "Farmer";
            currentcard.multiple++;
            printf("Multiple = %f.\nYou are the Load now.\n", pow(2,  currentcard.multiple));
            player1 = aftercallingload(player1, firstthree);
            memset(player2.hand+17, 0, 3 * sizeof(card));
            memset(player3.hand+17, 0, 3 * sizeof(card));
        } else {
            printf("Player2 is the Load now!\n");
            player2 = aftercallingload(player2, firstthree);
            memset(player1.hand+17, 0, 3 * sizeof(card));
            memset(player3.hand+17, 0, 3 * sizeof(card));
        }
    }
    else {
        currentcard.multiple = 1;
        printf("Player3 want to be the Load.\nMultiple = %f.\nDo you want to be the Load? [Y/N]\n", pow(2,  currentcard.multiple));
        char c;
        scanf("%c", &c);
        if (c == 'Y' || c == 'y') {
            currentcard.multiple++;
            player1.role = "Load";
            player3.role = "Farmer";
            printf("Multiple = %f.\nPlayer2 doesn't want to be the Load.\nYou are the Load now.\n", pow(2,  currentcard.multiple));
            player1 = aftercallingload(player1, firstthree);
            memset(player2.hand+17, 0, 3 * sizeof(card));
            memset(player3.hand+17, 0, 3 * sizeof(card));
        } else {
            printf("Player1 don't want to be the Load.\nPlayer2 doesn't want to be the Load.\nMultiple = %f.\nPlayer3 is the Load now!\n", pow(2,  currentcard.multiple));
            player3 = aftercallingload(player3, firstthree);
            memset(player1.hand+17, 0, 3 * sizeof(card));
            memset(player2.hand+17, 0, 3 * sizeof(card));
        }
    }

    for (int i = 0; i <= 19; i++){
        printf("~~%d,,%d,,%s~~\n", i+1, player1.hand[i].num, player1.hand[i].patt);
    }
    for (int i = 0; i <= 19; i++){
        printf("~~~~%d,,%d,,%s~~~~\n", i+1, player2.hand[i].num, player2.hand[i].patt);
    }
    for (int i = 0; i <= 19; i++){
        printf("~~~~~~%d,,%d,,%s~~~~~~\n", i+1, player3.hand[i].num, player3.hand[i].patt);
    }




    while (player1.numofhand > 0 || player2.numofhand > 0 || player3.numofhand > 0) {
        if (strncmp(player1.role, "Load", 4) == 0){
            printf("Player 1 is trying to show cards.\n");
            if (player2.cannotshow == 1 && player3.cannotshow == 1){
                currentcard = NPCshow_othernoshow(player1, currentcard);
                player1 = aftershowing(player1, currentcard);
            }else{
                currentcard = NPCshow(player1, currentcard);
                player1 = aftershowing(player1, currentcard);
            }
            printcurrentcard(player1, currentcard.cards);
            if (player1.numofhand == 0) break;

            printf("Player 2 is trying to show cards.\n");
            if (player1.cannotshow == 1 && player3.cannotshow == 1){
                currentcard = NPCshow_othernoshow(player2, currentcard);
                player2 = aftershowing(player2, currentcard);
            }else{
                currentcard = NPCshow(player2, currentcard);
                player2 = aftershowing(player2, currentcard);
            }
            printcurrentcard(player2, currentcard.cards);
            if (player1.numofhand == 0) break;

            printf("Player 3 is trying to show cards.\n");
            if (player1.cannotshow == 1 && player2.cannotshow == 1){
                currentcard = NPCshow_othernoshow(player3, currentcard);
                player3 = aftershowing(player3, currentcard);
            }else{
                currentcard = NPCshow(player3, currentcard);
                player3 = aftershowing(player3, currentcard);
            }
            printcurrentcard(player3, currentcard.cards);
            if (player1.numofhand == 0) break;
        }

        else if (strncmp(player2.role, "Load", 4) == 0){
            printf("Player 2 is trying to show cards.\n");
            if (player1.cannotshow == 1 && player3.cannotshow == 1){
                currentcard = NPCshow_othernoshow(player2, currentcard);
                player2 = aftershowing(player2, currentcard);
            }else{
                currentcard = NPCshow(player2, currentcard);
                player2 = aftershowing(player2, currentcard);
            }
            printcurrentcard(player2, currentcard.cards);
            if (player1.numofhand == 0) break;

            printf("Player 3 is trying to show cards.\n");
            if (player1.cannotshow == 1 && player2.cannotshow == 1){
                currentcard = NPCshow_othernoshow(player3, currentcard);
                player3 = aftershowing(player3, currentcard);
            }else{
                currentcard = NPCshow(player3, currentcard);
                player3 = aftershowing(player3, currentcard);
            }
            printcurrentcard(player3, currentcard.cards);
            if (player1.numofhand == 0) break;

            printf("Player 1 is trying to show cards.\n");
            if (player2.cannotshow == 1 && player3.cannotshow == 1){
                currentcard = NPCshow_othernoshow(player2, currentcard);
                player2 = aftershowing(player2, currentcard);
            }else{
                currentcard = NPCshow(player1, currentcard);
                player1 = aftershowing(player1, currentcard);
            }
            printcurrentcard(player1, currentcard.cards);
            if (player1.numofhand == 0) break;
        }
        else{
            printf("Player 3 is trying to show cards.\n");
            if (player1.cannotshow == 1 && player2.cannotshow == 1){
                currentcard = NPCshow_othernoshow(player3, currentcard);
                player3 = aftershowing(player3, currentcard);
            }else{
                currentcard = NPCshow(player3, currentcard);
                player3 = aftershowing(player3, currentcard);
            }
            printcurrentcard(player3, currentcard.cards);
            if (player1.numofhand == 0) break;

            printf("Player 1 is trying to show cards.\n");
            if (player2.cannotshow == 1 && player3.cannotshow == 1){
                currentcard = NPCshow_othernoshow(player2, currentcard);
                player2 = aftershowing(player2, currentcard);
            }else{
                currentcard = NPCshow(player1, currentcard);
                player1 = aftershowing(player1, currentcard);
            }
            printcurrentcard(player1, currentcard.cards);
            if (player1.numofhand == 0) break;

            printf("Player 2 is trying to show cards.\n");
            if (player3.cannotshow == 1 && player1.cannotshow == 1){
                currentcard = NPCshow_othernoshow(player2, currentcard);
                player2 = aftershowing(player2, currentcard);
            }else{
                currentcard = NPCshow(player2, currentcard);
                player2 = aftershowing(player2, currentcard);
            }
            printcurrentcard(player2, currentcard.cards);
            if (player1.numofhand == 0) break;
        }
    }


    if (player1.numofhand == 0){
        if (strncmp(player1.role, "Load", 4) == 0){
            printf("Player 1 wins!\n");
        }
        else if (strncmp(player2.role, "Load", 4) == 0){
            printf("Player 1 wins!\n");
            printf("Player 3 wins!\n");
        }
        else{
            printf("Player 1 wins!\n");
            printf("Player 2 wins!\n");
        }
    }
    if (player2.numofhand == 0){
        if (strncmp(player2.role, "Load", 4) == 0){
            printf("Player 2 wins!\n");
        }
        else if (strncmp(player3.role, "Load", 4) == 0){
            printf("Player 1 wins!\n");
            printf("Player 2 wins!\n");
        }
        else{
            printf("Player 2 wins!\n");
            printf("Player 3 wins!\n");
        }
    }
    if (player3.numofhand == 0){
        if (strncmp(player3.role, "Load", 4) == 0){
            printf("Player 3 wins!\n");
        }
        else if (strncmp(player1.role, "Load", 4) == 0){
            printf("Player 2 wins!\n");
            printf("Player 3 wins!\n");
        }
        else{
            printf("Player 1 wins!\n");
            printf("Player 3 wins!\n");
        }
    }

    printf("Game End!\n");
    free(player1.hand); free(player2.hand); free(player3.hand);
    free(currentcard.cards);
    return 0;
}
