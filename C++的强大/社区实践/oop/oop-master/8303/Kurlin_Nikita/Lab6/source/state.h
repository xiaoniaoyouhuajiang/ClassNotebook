#ifndef STATE_H
#define STATE_H

#include <string>
#include "basehandler.h"

class State{
public:
    State(){}
    virtual ~State(){}
    virtual void handle(std::string, BaseHandler*) = 0;

};

class Player1StepState : public State{
public:
    Player1StepState(){}
    void handle(std::string commandStr, BaseHandler* handler) override
    {
        handler->handle(commandStr, 1);
    }
};

class Player2StepState : public State{
public:
    Player2StepState(){}
    void handle(std::string commandStr, BaseHandler* handler) override
    {
        handler->handle(commandStr, 2);
    }
};

class Player3StepState : public State{
public:
    Player3StepState(){}
    void handle(std::string commandStr, BaseHandler* handler) override
    {
        handler->handle(commandStr, 3);
    }
};

#endif // STATE_H
