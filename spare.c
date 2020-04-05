card* NPCshow(player playerx, card *currentcard){
    int currentamount = countcard(currentcard);
    if (currentamount == 1) {           //单牌
        currentcard = find(currentcard, playerx.hand);
//        if (cardcode < 20) {
//                currentcard[0] = playerx.hand[cardcode];
//                for (int i = 1; i <= 19; i++) {
//                    currentcard[i].code = 0;
//                }

//                for (int i = cardcode; i <= playerx.numofhand - 1; i++) {
//                    playerx.hand[i] = playerx.hand[i + 1];
//                }
//                printcurrentcard(playerx, currentcard);
//                playerx.hand[playerx.numofhand].code = 0;
    }
    else if (currentamount == 2){          //对子
        currentcard = find(currentcard, playerx.hand);
//        int cardcode = 0;
//        for (cardcode = 0; cardcode <= 20; cardcode++) {
//            if (playerx.hand[cardcode].num > currentcard[0].num &&
//                playerx.hand[cardcode].num == playerx.hand[cardcode + 1].num &&
//                playerx.hand[cardcode + 1].num != playerx.hand[cardcode + 2].num)
//                break;
//        }
//        if (cardcode < 20) {
//            currentcard[0] = playerx.hand[cardcode];
//            currentcard[1] = playerx.hand[cardcode + 1];
//            for (int i = 2; i <= 19; i++) {
//                currentcard[i].code = 0;
//            }
//            playerx.numofhand -= 2;
//            for (int i = cardcode; i <= playerx.numofhand -1; i++) {
//                playerx.hand[cardcode] = playerx.hand[cardcode + 2];
//            }
//            printcurrentcard(playerx, currentcard);
//            playerx.hand[playerx.numofhand].code = 0;
//            playerx.hand[playerx.numofhand + 1].code = 0;
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