//
// Created by shenk on 15.04.2020.
//

#ifndef UNTITLED13_GAMERULE_H
#define UNTITLED13_GAMERULE_H


class GameInfo;

class GameRule {

public:
    int fieldWidth;
    int fieldHeight;
    virtual bool isOver(GameInfo &gameInfo)=0;
    virtual int nextUser(GameInfo &gameInfo)=0;

    GameRule(int fieldWidth, int fieldHeight):
    fieldWidth(fieldWidth),
    fieldHeight(fieldHeight){}

};


#endif //UNTITLED13_GAMERULE_H
