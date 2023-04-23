
#ifndef context_hpp
#define context_hpp

#include <stdio.h>
#include <iostream>

#include "StateAbstract.hpp"
#include "player2.hpp"
#include "player1.hpp"


class Context {
    
private:
    State *state_;
    
public:
    Context(State *state) : state_(nullptr) {
        this->TransitionTo(state);
    }
    ~Context() {
        delete state_;
    }
    
    void TransitionTo(State *state) {
        if (this->state_ != nullptr)
            delete this->state_;
        this->state_ = state;
        this->state_->set_context(this);
    }
    
    ACTION RequestInput() {
        ACTION x = this->state_->getInputAction();
        if(typeid(*state_).name() == typeid(*new Player1).name()){
            TransitionTo(new Player2);
        }else{
            TransitionTo(new Player1);
        }
        return x;
    }
    
};

#endif /* context_hpp */
