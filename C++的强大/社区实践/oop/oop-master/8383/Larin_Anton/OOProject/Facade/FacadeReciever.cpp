//
// Created by anton on 5/31/20.
//

#include "FacadeReciever.h"

const std::pair<int, int> &FacadeReciever::getSelectionA() const {
    return activeState->getSelectionA();
}

const std::pair<int, int> &FacadeReciever::getSelectionB() const {
    return activeState->getSelectionB();;
}

void FacadeReciever::setSelectionA(const std::pair<int, int> &selectionA) {
    activeState->setSelectionA(selectionA);
}

void FacadeReciever::setSelectionB(const std::pair<int, int> &selectionB) {
    activeState->setSelectionB(selectionB);
}

bool FacadeReciever::act() {
    return activeState->act();
}

bool FacadeReciever::step() {
    return activeState->step();
}

std::vector<std::vector<FlyCell>> FacadeReciever::getFW() {
    return activeState->getFW();
}

bool FacadeReciever::summon(int x, int y, UnitClass unitClass) {
    return activeState->summon(x,y,unitClass);
}

FacadeReciever::FacadeReciever(const std::shared_ptr<Mediator> &mediator)
        : mediator(mediator) {

}

void FacadeReciever::init(bool firstA, std::shared_ptr<Actor> actorA, std::shared_ptr<Actor> actorB) {
    auto This = shared_from_this();
    assert(This.use_count()>1);

    auto sA = std::make_shared<State>(mediator,std::weak_ptr<FacadeReciever>(This),actorA,Devotion::Light);
    stateA  = sA;
    auto sB = std::make_shared<State>(mediator,std::weak_ptr<FacadeReciever>(This),actorB,Devotion::Dark);
    stateB = sB;
    sA->setNextState(sB);
    sB->setNextState(sA);
    exitFlag= false;
    restartFlag= false;
    activeState=firstA?sA:sB;
}


void FacadeReciever::next() {
    assert(activeState.use_count()>1);
    auto ns = activeState->nextState;
    if(auto sns = ns.lock()){
        assert(sns.use_count()>1);
        activeState=sns;
    }
}

void FacadeReciever::exit() {
    exitFlag=true;
}

void FacadeReciever::restart() {
    restartFlag= true;
}

std::weak_ptr<Actor> FacadeReciever::whosTurn() {
    return std::weak_ptr<Actor>(activeState->actor);
}



void FacadeReciever::turn() {
    activeState->actor->turn();
}

bool FacadeReciever::isExitFlag() const {
    return exitFlag;
}

bool FacadeReciever::isRestartFlag() const {
    return restartFlag;
}

Devotion FacadeReciever::turnDevotion() {
    return activeState->devotion;
}

std::pair<int, std::pair<int, int>> FacadeReciever::getBaseStats(Devotion devotion) {
    return mediator->getBaseStats(devotion);
}


