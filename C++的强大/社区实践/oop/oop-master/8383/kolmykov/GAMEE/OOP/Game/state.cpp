#include "state.h"


State::State(Kind kind, int num, std::shared_ptr<Field> field, std::shared_ptr<Facade> facade) {
    this->kind = kind;
    this->playerNum = num;
    this->field = field;
    this->facade = facade;

    resources = 5;

    switch(kind) {
    case Kind::HUMAN:
        yT = field->getHeight() - 1;
        yU = yT - 1;
        break;
    case Kind::ZOMBY:
        yT = 0;
        yU = 1;
    }
}


Kind State::getKind() {
    return kind;
}


int State::getPlayerNum(){
    return playerNum;
}


void State::create(int xT, int xU,  UnitType type) {

}


void State::endStep() {

}


void State::setNextState(std::shared_ptr<State> state) {
    nextState = state;
}
std::shared_ptr<State> State::getNextState() {
    return nextState;
}


void State::renewResources() {
    resources = 5;
}

int State::getResources() {
    return resources;
}


StateType State::getType() {
    return type;
}


void State::setResources(int resources) {
    this->resources = resources;
}
