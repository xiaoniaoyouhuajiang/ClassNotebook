//
// Created by shenk on 18.03.2020.
//

#ifndef UNTITLED13_GAMEINFO_H
#define UNTITLED13_GAMEINFO_H

#include "UI/Commands/CommandMemento.h"
#include "GameField/GameField.h"
#include "Rules/GameRule.h"
#include "Exceptions/DoubleBasePlacingException.h"

class GameInfo {

protected:

    GameField gameField;
    std::vector<Base*> playersBases;
    int nowPlayerIndex;
    std::vector<CommandMemento*> history;
    GameRule *rule;

public:

    GameInfo(int playersCount, int fieldWidth, int fieldHeight, GameRule *rule):
    gameField(fieldHeight, fieldWidth),
    playersBases(playersCount, nullptr),
    nowPlayerIndex(0),
    rule(rule)
    {}

    Base *getNowPlayerBase(){ return playersBases[nowPlayerIndex]; }
    bool setNowPlayerBase(Base *base){

        if (playersBases[nowPlayerIndex]){
            throw DoubleBasePlacingException(nowPlayerIndex);
        } else{

            playersBases[nowPlayerIndex] = base;
            return true;

        }

    }
    int getNowPlayerIndex(){ return nowPlayerIndex; }

    void newGame(){

        int playersCount = playersBases.size();

        gameField.reset();
        playersBases.clear();
        history.clear();
        playersBases.resize(playersCount, nullptr);

    }
    void nextUser(){
        nowPlayerIndex = rule->nextUser(*this);
    }

    void addToHistory(CommandMemento *memento){

        history.push_back(memento);

    }

    std::vector<CommandMemento*> getHistory(){ return history; };
    GameField &getField(){ return gameField; }
    const std::vector<Base*> &getBases(){
        return playersBases;
    }

};


#endif //UNTITLED13_GAMEINFO_H
