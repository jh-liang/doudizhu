#include "function.h"

int main() {
    card *deck = calloc(54, sizeof(card));  //所有牌


    player player1 = {"", calloc(17, sizeof(card)),17, 1, 0};
    player player2 = {"", calloc(17, sizeof(card)),17, 2, 0};
    player player3 = {"", calloc(17, sizeof(card)),17, 3, 0};

    card *firstthree = calloc(54, sizeof(card));             //开局三张地主牌
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

    current currentcard = {calloc(20, sizeof(currentcard)), 0, 0};                 //牌桌上现在的牌组
    

    if (strncmp(player1.role, "Load", 4) == 0) {    //Load = 地主
        printf("Do you want to be the Load? Input your point! (0 - 2)");    //叫地主
        scanf("%d", &currentcard.multiple);
        if ( currentcard.multiple == 0 && deck[1].num < 6) {
            printf("You don't want to be the Load.\nPlayer 2 doesn't want to be the Load.\nPlayer 3 wants to be the Load.\nMultiple = %f.\n",
                   pow(2,  currentcard.multiple));
            player1.role = "farmer.";
            player3.role = "Load";
            player3 = aftercallingload(player3, firstthree);          //叫地主后的给牌程序
        } else if ( currentcard.multiple == 0 && deck[1].num >= 6) {
             currentcard.multiple = 2;
            printf("You don't want to be the Load.\nPlayer 2 wants to be the Load.\nMultiple = %f.\nPlayer 3 doesn't want to be the Load.\n",
                   pow(2,  currentcard.multiple));
            player1.role = "farmer.";
            player2.role = "Load";
            player2 = aftercallingload(player2, firstthree);
        } else {
            printf("You want to be the Load.\nPlayer 2 doesn't want to be the Load.\nPlayer 3 doesn't want to be the Load.\nMultiple = %f.\n",
                   pow(2,  currentcard.multiple));
            player1 = aftercallingload(player1, firstthree);
        }
    } else {
        if (strncmp(player2.role, "Load", 4) == 0) {
             currentcard.multiple++;
            printf("Player2 wants to be the Load.\nMultiple = %f.\nPlayer 3 doesn't want to be the Load.\nDo you want to be the Load? [Y/N]",
                   pow(2,  currentcard.multiple));
            char c;
            scanf("%c", &c);
            if (c == 'Y' || c == 'y') {
                player1.role = "Load";
                player2.role = "farmer";
                 currentcard.multiple++;
                printf("Multiple = %f.\nYou are the Load now.\n", pow(2,  currentcard.multiple));
                player1 = aftercallingload(player1, firstthree);
            } else {
                printf("Player2 is the Load now!\n");
                player2 = aftercallingload(player2, firstthree);
            }
        }
        if (strncmp(player3.role, "Load", 4) == 0) {
             currentcard.multiple++;
            printf("Player3 want to be the Load.\nMultiple = %f.\nDo you want to be the Load? [Y/N]", pow(2,  currentcard.multiple));
            char c;
            scanf("%c", &c);
            if (c == 'Y') {
                 currentcard.multiple++;
                player1.role = "Load";
                player3.role = "farmer";
                printf("Multiple = %f.\nPlayer2 doesn't want to be the Load.\nYou are the Load now.\n", pow(2,  currentcard.multiple));
                player1 = aftercallingload(player1, firstthree);
            } else {
                printf("Player1 don't want to be the Load.\nPlayer2 doesn't want to be the Load.\nPlayer3 is the Load now!\n");
                player3 = aftercallingload(player3, firstthree);
            }
        }
    }

    while (player1.numofhand > 0 || player2.numofhand > 0 || player3.numofhand > 0) {
        if (strncmp(player1.role, "Load", 4) == 0){
            printf("Player 1 is trying to show cards.\n");
            if ((player2.cannotshow == 1 && player3.cannotshow == 1) || currentcard.cards[0].num == 0){
                currentcard = NPCshow_othernoshow(player1, currentcard);
                player1 = aftershowing(player1, currentcard.cards);
                printf("Checkpoint3\n");
            }else{
                currentcard = NPCshow(player1, currentcard);
                player1 = aftershowing(player1, currentcard.cards);
            }
            printcurrentcard(player1, currentcard.cards);


            printf("Player 2 is trying to show cards.\n");
            if (player1.cannotshow == 1 && player3.cannotshow == 1){
                currentcard = NPCshow_othernoshow(player2, currentcard);
                player2 = aftershowing(player2, currentcard.cards);
            }else{
                currentcard = NPCshow(player2, currentcard);
                player2 = aftershowing(player2, currentcard.cards);
            }
            printcurrentcard(player2, currentcard.cards);


            printf("Player 3 is trying to show cards.\n");
            if (player1.cannotshow == 1 && player2.cannotshow == 1){
                currentcard = NPCshow_othernoshow(player3, currentcard);
                player3 = aftershowing(player3, currentcard.cards);
            }else{
                currentcard = NPCshow(player3, currentcard);
                player3 = aftershowing(player3, currentcard.cards);
            }
            printcurrentcard(player3, currentcard.cards);
        }

        else if (strncmp(player2.role, "Load", 4) == 0){
            printf("Player 2 is trying to show cards.\n");
            if ((player1.cannotshow == 1 && player3.cannotshow == 1) || currentcard.cards[0].num == 0){
                currentcard = NPCshow_othernoshow(player2, currentcard);
                player2 = aftershowing(player2, currentcard.cards);
            }else{
                currentcard = NPCshow(player2, currentcard);
                player2 = aftershowing(player2, currentcard.cards);
            }
            printcurrentcard(player2, currentcard.cards);


            printf("Player 3 is trying to show cards.\n");
            if (player1.cannotshow == 1 && player2.cannotshow == 1){
                currentcard = NPCshow_othernoshow(player3, currentcard);
                player3 = aftershowing(player3, currentcard.cards);
            }else{
                currentcard = NPCshow(player3, currentcard);
                player3 = aftershowing(player3, currentcard.cards);
            }
            printcurrentcard(player3, currentcard.cards);


            printf("Player 1 is trying to show cards.\n");
            if (player2.cannotshow == 1 && player3.cannotshow == 1){
                currentcard = NPCshow_othernoshow(player2, currentcard);
                player2 = aftershowing(player2, currentcard.cards);
            }else{
                currentcard = NPCshow(player1, currentcard);
                player1 = aftershowing(player1, currentcard.cards);
            }
            printcurrentcard(player1, currentcard.cards);
        }
        else{
            printf("Player 3 is trying to show cards.\n");
            if ((player1.cannotshow == 1 && player2.cannotshow == 1) || currentcard.cards[0].num == 0){
                currentcard = NPCshow_othernoshow(player3, currentcard);
                player3 = aftershowing(player3, currentcard.cards);
            }else{
                currentcard = NPCshow(player3, currentcard);
                player3 = aftershowing(player3, currentcard.cards);
            }
            printcurrentcard(player3, currentcard.cards);

            printf("Player 1 is trying to show cards.\n");
            if (player2.cannotshow == 1 && player3.cannotshow == 1){
                currentcard = NPCshow_othernoshow(player2, currentcard);
                player2 = aftershowing(player2, currentcard.cards);
            }else{
                currentcard = NPCshow(player1, currentcard);
                player1 = aftershowing(player1, currentcard.cards);
            }
            printcurrentcard(player1, currentcard.cards);

            printf("Player 2 is trying to show cards.\n");
            if (player3.cannotshow == 1 && player1.cannotshow == 1){
                currentcard = NPCshow_othernoshow(player2, currentcard);
                player2 = aftershowing(player2, currentcard.cards);
            }else{
                currentcard = NPCshow(player2, currentcard);
                player2 = aftershowing(player2, currentcard.cards);
            }
            printcurrentcard(player2, currentcard.cards);
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
    return 0;
}
