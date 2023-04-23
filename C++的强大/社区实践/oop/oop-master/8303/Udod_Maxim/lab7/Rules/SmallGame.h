//
// Created by shenk on 15.04.2020.
//

#ifndef UNTITLED13_SMALLGAME_H
#define UNTITLED13_SMALLGAME_H

#include "GameRule.h"
#include "Players/PlayerState.h"

class SmallGame: public GameRule {

private:

    PlayerState* nowState;

public:

    SmallGame(): GameRule( 3, 3), nowState(new FirstPlayer){}

    bool isOver(GameInfo &gameInfo) override {
        int liveCount = gameInfo.getBases().size();
        for (auto b: gameInfo.getBases()){
            if (b && b->getHealth() <= 0){
                liveCount--;
            }
        }

        return liveCount <= 1;
    }

    int nextUser(GameInfo &gameInfo) override {

        int nowPlayerIndex = gameInfo.getNowPlayerIndex()+nowState->getNextPlayerDelta();
        nowPlayerIndex %= gameInfo.getBases().size();
        auto nextState = nowState->getNextPlayerState();
        delete nowState;
        nowState = nextState;
        if (nowState == nullptr)
            nowState = new FirstPlayer;
        return nowPlayerIndex;

    }

};


#endif //UNTITLED13_SMALLGAME_H
