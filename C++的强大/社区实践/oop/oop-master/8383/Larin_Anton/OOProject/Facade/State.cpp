//
// Created by anton on 5/31/20.
//

#include "State.h"
#include "../Mediator.h"

#include "FacadeReciever.h"

const std::pair<int, int> &State::getSelectionA()const {
    return mediator->getSelectionA();
}

const std::pair<int, int> &State::getSelectionB()const {
    return mediator->getSelectionB();
}

void State::setSelectionA(const std::pair<int, int> &selectionA) {
    mediator->setSelectionA(selectionA);
}

void State::setSelectionB(const std::pair<int, int> &selectionB) {
    mediator->setSelectionB(selectionB);
}

bool State::act() {
    std::pair<int,int> selA = getSelectionA();
    std::pair<int,int> selB = getSelectionB();
    FlyCell fcA = mediator->getFlyCellAt(selA.first,selA.second);
    FlyCell fcB = mediator->getFlyCellAt(selB.first,selB.second);

    if(!fcA.getUnit())return false;//No attacker
    if(fcA.getUnit()->devotion!=devotion)return false;//Attacker is not an ally
    if(fcB.getUnit() && fcB.getUnit()->devotion==devotion) return false;//Target is an ally

    return mediator->act();
}

bool State::step() {
    std::pair<int,int> selA = getSelectionA();
    std::pair<int,int> selB = getSelectionA();
    FlyCell fcA = mediator->getFlyCellAt(selA.first,selA.second);
    FlyCell fcB = mediator->getFlyCellAt(selB.first,selB.second);

    if(!fcA.getUnit())return false;//No attacker
    if(fcA.getUnit()->devotion!=devotion)return false;//Attacker is not an ally

    bool flag =  mediator->step();
    if(flag)next();
    return flag;
}

std::vector<std::vector<FlyCell>> State::getFW() {

}

void State::onEnter() {
    //this->actor->turn();
}

void State::next() {
    if(auto fr = facadeReciever.lock()){
        fr->next();
    }else{
        assert(0);
    }
}

bool State::summon(int x, int y, UnitClass unitClass) {
    bool flag = mediator->createObject(x,y,devotion,unitToCommon(unitClass));
    next();
    return flag;
}

State::State(const std::shared_ptr<Mediator> &mediator, const std::weak_ptr<FacadeReciever> &facadeReciever,
             const std::shared_ptr<Actor> &actor, Devotion devotion) : mediator(mediator),
                                                                       facadeReciever(facadeReciever), actor(actor),
                                                                       devotion(devotion) {}

const std::weak_ptr<State> &State::getNextState() const {
    return nextState;
}

void State::setNextState(const std::weak_ptr<State> &nextState) {
    State::nextState = nextState;
}

Devotion State::getDevotion() const {
    return devotion;
}

void State::exit() {
    assert(0);
}

void State::restart() {
    assert(0);
}

std::pair<int, std::pair<int, int>> State::getBaseStats(Devotion devotion) {
    return mediator->getBaseStats(devotion);
}
