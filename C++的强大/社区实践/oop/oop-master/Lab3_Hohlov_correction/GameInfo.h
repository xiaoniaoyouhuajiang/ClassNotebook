
#ifndef UNTITLED13_GAMEINFO_H
#define UNTITLED13_GAMEINFO_H

#include "GameField/GameField.h"

class GameInfo {

protected:

    GameField gameField;
    std::vector<Base*> playersBases;
    int nowPlayerIndex;

public:

    GameInfo(int playersCount, int fieldWidth, int fieldHeight):
    gameField(fieldHeight, fieldWidth),
    playersBases(playersCount, nullptr),
    nowPlayerIndex(0)
    {}

    Base *getNowPlayerBase(){ return playersBases[nowPlayerIndex]; }
    bool setNowPlayerBase(Base *base){

        if (playersBases[nowPlayerIndex]){
            return false;
        } else{

            playersBases[nowPlayerIndex] = base;

        }

    }
    bool isOver() {

        return false;

    }

};


#endif //UNTITLED13_GAMEINFO_H
