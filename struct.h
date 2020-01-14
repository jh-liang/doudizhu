//
// Created by zxj on 2020/1/14.
//

#ifndef DOUDIZHU_STRUCT_H
#define DOUDIZHU_STRUCT_H

typedef struct _card {
    char *patt; //花色 在这游戏里没啥用
    int num;    //大小
    int code;   //代号 方便管理卡牌
} card;

typedef struct _player {
    char *role;     //农民or地主
    card hand[20];  //手牌
    int numofhand;  //手牌数目
    int code;       //玩家编号123
} player;

#endif //DOUDIZHU_STRUCT_H
