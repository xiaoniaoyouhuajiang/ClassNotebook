//
// Created by shenk on 16.04.2020.
//

#ifndef UNTITLED13_PLAYERSTATE_H
#define UNTITLED13_PLAYERSTATE_H


class PlayerState {

public:

    virtual int getNextPlayerDelta()=0;
    virtual PlayerState* getNextPlayerState()=0;

};

class SecondPlayer: public PlayerState {

    int getNextPlayerDelta() override{
        return 2;
    }

    PlayerState* getNextPlayerState() override{
        return nullptr;
    }

};

class ThirdPlayer: public PlayerState {

    int getNextPlayerDelta() override{
        return -1;
    }

    PlayerState* getNextPlayerState() override{
        return new SecondPlayer;
    }

};

class FirstPlayer: public PlayerState {

public:

    int getNextPlayerDelta() override{
        return 2;
    }

    PlayerState* getNextPlayerState() override{

        return new ThirdPlayer;

    }

};
#endif //UNTITLED13_PLAYERSTATE_H
