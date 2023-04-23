//
// Created by alexg on 03.06.2020.
//

#ifndef LABS_STATE_H
#define LABS_STATE_H

#include <string>

#include "../extra3/ChainOfCommand.h"

class State{
public:
    virtual void handle(std::string command, chainOfResponsibility *basecomm) = 0;
};

class State1: public State{
public:
    void handle(std::string command, chainOfResponsibility *basecomm) override {
        //basecomm->chainOR(command, "0");
    }
};

class State2: public State{
public:
    void handle(std::string command, chainOfResponsibility *basecomm) override {
        //basecomm->chainOR(command, "1");
    }
};

#endif //LABS_STATE_H
