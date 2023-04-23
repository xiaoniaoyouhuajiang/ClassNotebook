#include "StateContext.h"

StateContext::StateContext() {
    curr = new State1();
    next = new State2();
    state = 0;
}

StateContext::~StateContext() {
    delete curr;
    delete next;
}

bool StateContext::handle(std::string s) {
    return curr->handle(s);
}

void StateContext::nextState() {
    State* tmp;

    tmp = curr;
    curr = next;
    next = tmp;
    state++;
    state %= 2;
}

int StateContext::getState() { 
    return state; 
}

void StateContext::setState(int state) {
    this->state = state;
}
