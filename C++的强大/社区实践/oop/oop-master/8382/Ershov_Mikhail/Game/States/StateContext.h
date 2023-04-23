#pragma once

#include "State1.h"
#include "State2.h"

class StateContext {
public:
    StateContext();
    ~StateContext();
    bool handle(std::string s);
    void nextState();
    int getState();
    void setState(int state);   //for load a game

private:
    State* curr;
    State* next;
    int state;
};
