//
// Created by shenk on 18.03.2020.
//

#ifndef UNTITLED13_GAMEINFO_H
#define UNTITLED13_GAMEINFO_H

#include "UI/Commands/CommandMemento.h"
#include "GameField/GameField.h"

class GameInfo {

protected:

    GameField gameField;
    std::vector<Base*> playersBases;
    int nowPlayerIndex;
    std::vector<CommandMemento*> history;

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
            return true;

        }

    }
    void newGame(){

        int playersCount = playersBases.size();

        gameField.reset();
        playersBases.clear();
        history.clear();
        playersBases.resize(playersCount, nullptr);

    }

    void addToHistory(CommandMemento *memento){

        history.push_back(memento);

    }

    void nextUser(){

        nowPlayerIndex++;
        if (nowPlayerIndex >= playersBases.size())
            nowPlayerIndex = 0;

    }

    bool isOver() { return false; }

    std::vector<CommandMemento*> getHistory(){ return history; };
    GameField &getField(){ return gameField; }

};


#endif //UNTITLED13_GAMEINFO_H
