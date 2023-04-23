#ifndef OOP1_STATE_H
#define OOP1_STATE_H

#include <string>
#include "Handler.h"

class State{
public:
    virtual void handle(std::string command, BaseHandler* baseHandler) = 0;
};

class State1: public State{
public:
    void handle(std::string command, BaseHandler* baseHandler) override {
        baseHandler->handle(command, 1);
    }
};

class State2: public State{
public:
    void handle(std::string command, BaseHandler* baseHandler) override {
        baseHandler->handle(command, 2);
    }
};

class State3: public State{
public:
    void handle(std::string command, BaseHandler* baseHandler) override {
        baseHandler->handle(command, 3);
    }
};

#endif //OOP1_STATE_H
