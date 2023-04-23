//
// Created by shenk on 16.04.2020.
//

#ifndef UNTITLED13_BIGGAME_H
#define UNTITLED13_BIGGAME_H

#include "GameRule.h"
#include "Players/PlayerState.h"

class BigGame: public GameRule {

private:

    PlayerState* nowState;

public:

    BigGame(): GameRule( 10, 10), nowState(new FirstPlayer){}

    bool isOver(GameInfo &gameInfo) override {
        return false;
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



#endif //UNTITLED13_BIGGAME_H
