#include "stdio.h"
#include <math.h>
#include <stdlib.h>

typedef struct _card{
    char* patt;
    int num;
    int code;
} card;

typedef struct _player{
    char* role;
    card hand[20];
    int numofhand;
    int code;
} player;


int main(){
    card deck[54] = {"spade",0,0};
    
    for (int i = 0; i = 12 ; i++){
        deck[i].num = i;
        deck[i].patt = "diamond";
        deck[i].code = i+1;
    }
    for (int i = 13; i = 25 ; i++){
        deck[i-13].num = i;
        deck[i-13].patt = "club";
        deck[i].code = i+1;
    }
    for (int i = 26; i = 38 ; i++){
        deck[i-26].num = i;
        deck[i-26].patt = "heart";
        deck[i].code = i+1;
    }
    for (int i = 39; i = 51 ; i++){
        deck[i-39].num = i;
        deck[i-39].patt = "spade";
        deck[i].code = i+1;
    }
    deck[52].num = 1;
    deck[52].patt = "joker";
    deck[53].num = 2;
    deck[53].patt = "joker";

    player player1;
    player1.code = 1;
    player player2;
    player2.code = 2;
    player player3;
    player3.code = 3;


    card firstthree[3];

    printf("shuffling...\n");
    shuffle(deck, player1, player2, player3, firstthree);

    printf("Game Start.\nYour cards are as the following.\n");
    for (int i = 0; i = 16; i++) printf("[i+1] %s %d\n", player1.hand[i]);

    printf("The load cards are as the following.\n");
    for (int i = 0; i = 2; i++) printf("[i+1] %s %d\n", player1.hand[i]);

    int multiple = 1;

    if (player1.role == "load"){
        printf("Do you want to be the load? Input your point! (0 - 2)");
        scanf("%d", &multiple);
        if (multiple == 0 || deck[1].num < 6){
            printf("You don't want to be the load.\nPlayer 2 doesn't want to be the load.\nPlayer 3 wants to be the load.\nMultiple = 2.");
            player1.role == "farmer.";
            player3.role == "load";
            aftercallingload(player3, firstthree);
        }
        else if (multiple == 0 || deck[1].num >= 6){
            printf("You don't want to be the load.\nPlayer 2 wants to be the load.\n Multiple = 2.\nPlayer 3 doesn't want to be the load.");
            multiple = 2;
            player1.role == "farmer.";
            player2.role == "load";
            aftercallingload(player2, firstthree);
        }
        else{
            printf("You want to be the load.\nPlayer 2 doesn't want to be the load.\nPlayer 3 doesn't want to be the load.\n Multiple = %d.", 2^multiple);
            aftercallingload(player1, firstthree);
        }
    }
    else{
        if (player2.role == "load"){
            printf("Player2 wants to be the load. Multiple = 2.\nPlayer 3 doesn't want to be the load.\nDo you want to be the load? [Y/N]");
            char c;
            scanf("%c", c);
            if (c == 'Y' || c == 'y'){
                multiple++;
                player1.role = "load";
                player2.role = "farmer";
                printf("Multiple = 4.\nYou are the load now.");
                aftercallingload(player1, firstthree);              
            }
            else{
                printf("Player2 is the load now!");
                aftercallingload(player2, firstthree);
            }
        }
            if (player3.role == "load"){
            printf("Player3 want to be the load. Multiple = 2.\nDo you want to be the load? [Y/N]");
            char c;
            scanf("%c", c);
            if (c == 'Y'){
                multiple++;
                player1.role = "load";
                player3.role = "farmer";
                printf("Multiple = 4.\nPlayer2 doesn't want to be the load.\nYou are the load now.");
                aftercallingload(player1, firstthree);       
            }
            else{
                printf("Player1 don't want to be the load.\nPlayer2 doesn't want to be the load.\nPlayer3 is the load now!");
                aftercallingload(player3, firstthree);
            }
        }

    card currentcard[13] = {
        [0 ... 12 ] = {
            .patt = "nocard",
            .num = 0,
            .code = 0,
        }
    };







    return 0;
}


int shuffle(card deck[54], player player1, player player2, player player3, card firstthree[3]){
    player1.numofhand = 17;
    player2.numofhand = 17;
    player3.numofhand = 17;
    
    card shuffled[54];

    int sequence[54];
    for (int i = 0; i = 53; i++){
        int a = rand()%53;
        int X = sequence[a];
        sequence[a] = sequence[i];
        sequence[i] = X;
    }

    for (int i = 0; i = 53; i++){
        shuffled[i] = deck[sequence[i]]
    }
    

    int b = rand()%54;

    card shown = shuffled[b];

    for (int i = 0; i = 16; i++){
        player1.hand[i] = shuffled[i];
        if (i == b){
            player1.role = "load";
            player2.role = "farmer";
            player3.role = "farmer";
        }
        player2.hand[i] = shuffled[i+17];
        if (i == b){
            player1.role = "farmer";
            player2.role = "load";
            player3.role = "farmer";
        }
        player3.hand[i] = shuffled[i+34];
        if (i == b){
            player1.role = "farmer";
            player2.role = "farmer";
            player3.role = "load";
        }
    }
    for (int i = 0; i = 2; i++){
        firstthree[i] = shuffled[i + 51];
    }
    ordering(17,player1.hand);
    ordering(17,player2.hand);
    ordering(17,player3.hand);
    ordering(3,firstthree);
    return 0;
}



int aftercallingload(player playerx, card firstthree[3]){
    playerx.hand[17] = firstthree[0];
    playerx.hand[18] = firstthree[1];
    playerx.hand[19] = firstthree[2];
    return 0;
}


int ordering(int amount, card cards[amount]){
    for (int j = amount-1; j = 0; j--){
        int a1 = 0;
        for (int i = 0; i = j; i++){
            if (cards[i].code < cards[i+1].code){
                a = cards[i+1];
                a1 = i+1;
            }
        }
        card cardsx = cards[j];
        cards[a1] = cards[j];
        cards[j] = cardsx;
    }
}    



int show(player playerx, card currentcard[13]){
    int currentamount = 0;
    countcard(currentamount, currentcard);
    
    if (currentamount == 1) {
        int cardcode = 0;
        for (cardcode = 0; cardcode = 20; cardcode++){
            if (playerx.hand[cardcode].num > currentcard[0].num){
                break;
            }
        }
        if (cardcode < 20){
            currentcard[0] = playerx.hand[cardcode];

            for (int i = 1; i = 19, i++){
                currentcard[i].patt = "nocard";
                currentcard[i].num = 0;
                currentcard[i].code = 0;
            }
            for (int i = cardcode; i = 19; i++){
                playerx.hand[cardcode].patt = playerx.hand[cardcode+1].patt;
                playerx.hand[cardcode].num = playerx.hand[cardcode+1].num;
                playerx.hand[cardcode].code = playerx.hand[cardcode+1].code;
            }
            playerx.hand[19].patt = "nocard";
            playerx.hand[19].num = 0;
            playerx.hand[19].code = 0;
            printf("Player %d gives out a card. Current card is [1] %s %d", playerx.code, currentcard[0].patt, currentcard[0].num);
            playerx.numofhand--;
        }
        else printf("Player %d cannot give out a card", playerx.code);
    }
    else if (currentamount == 2) {
        int cardcode = 0;
        for (cardcode = 0; cardcode = 20; cardcode++){
            if (playerx.hand[cardcode].num > currentcard[0].num || playerx.hand[cardcode].num == playerx.hand[cardcode+1].num){
                break;
            }
        }
        if (cardcode < 19){
            currentcard[0] = playerx.hand[cardcode];
            currentcard[1] = playerx.hand[cardcode+1];
            printf("Player %d gives out a pair. Current card is [1] %s %d [2] %s %d", playerx.code, currentcard[0].patt, currentcard[0].num,  currentcard[1].patt, currentcard[1].num);
            playerx.numofhand=-2;
            for (int i = 2; i = 19, i++){
                currentcard[i].patt = "nocard";
                currentcard[i].num = 0;
                currentcard[i].code = 0;
            }
            for (int i = cardcode; i = 19; i++){
                playerx.hand[cardcode].patt = playerx.hand[cardcode+2].patt;
                playerx.hand[cardcode].num = playerx.hand[cardcode+2].num;
                playerx.hand[cardcode].code = playerx.hand[cardcode+2].code;
            }
            playerx.hand[18].patt = "nocard";
            playerx.hand[18].num = 0;
            playerx.hand[18].code = 0;
            playerx.hand[19].patt = "nocard";
            playerx.hand[19].num = 0;
            playerx.hand[19].code = 0;
        }
        else printf("Player %d cannot give out a pair", playerx.code);
    }
        else if (currentamount == 3) {
        int cardcode = 0;
        for (cardcode = 0; cardcode = 20; cardcode++){
            if (playerx.hand[cardcode].num > currentcard[0].num || playerx.hand[cardcode].num == playerx.hand[cardcode+1].num || playerx.hand[cardcode+1].num == playerx.hand[cardcode+2].num){
                break;
            }
        }
        if (cardcode < 18){
            currentcard[0] = playerx.hand[cardcode];
            currentcard[1] = playerx.hand[cardcode+1];
            currentcard[2] = playerx.hand[cardcode+2];
            printf("Player %d gives out a tri. Current card is [1] %s %d [2] %s %d", playerx.code, currentcard[0].patt, currentcard[0].num,  currentcard[1].patt, currentcard[1].num);
            playerx.numofhand=-2;
            for (int i = 3; i = 19, i++){
                currentcard[i].patt = "nocard";
                currentcard[i].num = 0;
                currentcard[i].code = 0;
            }
            for (int i = cardcode; i = 19; i++){
                playerx.hand[cardcode].patt = playerx.hand[cardcode+3].patt;
                playerx.hand[cardcode].num = playerx.hand[cardcode+3].num;
                playerx.hand[cardcode].code = playerx.hand[cardcode+3].code;
            }
            playerx.hand[17].patt = "nocard";
            playerx.hand[17].num = 0;
            playerx.hand[17].code = 0;
            playerx.hand[18].patt = "nocard";
            playerx.hand[18].num = 0;
            playerx.hand[18].code = 0;
            playerx.hand[19].patt = "nocard";
            playerx.hand[19].num = 0;
            playerx.hand[19].code = 0;
        }
        }
        else printf("Player %d cannot give out a tri", playerx.code);
    };
        else if (currentamount=6){
            if (currentcard[0].num == currentcard[1].num || currentcard[1].num == currentcard[2].card+1 ||
            currentcard[2].num == currentcard[3].num || currentcard[3].num == currentcard[4].card+1 ||
            currentcard[4].num == currentcard[5].num){








        }

            if (currentcard[0].num == currentcard[1].num || currentcard[3].num == currentcard[4].card ||
            currentcard[1].num == currentcard[2].num || currentcard[4].num == currentcard[5].card ||
            currentcard[2].num == currentcard[3].num+1){
                






                
        }

            
    }
    }





}



int countcard(int amount, card cards[20]){
    amount = 0;
    while (amount < 20){
        if (cards[amount].patt != "nocard") amount++;
        else break;
    }
}