//
// Created by anton on 5/31/20.
//

#include "Actor.h"

#include "../FlyCell.h"

const std::pair<int, int> &Actor::getSelectionA() const {
    return composer->getSelectionA();
}

const std::pair<int, int> &Actor::getSelectionB() const {
    return composer->getSelectionB();
}

void Actor::setSelectionA(const std::pair<int, int> &selectionA) {
    composer->setSelectionA(selectionA);
}

void Actor::setSelectionB(const std::pair<int, int> &selectionB) {
    composer->setSelectionB(selectionB);
}

bool Actor::act() {
    return composer->act();
}

bool Actor::step() {
    return composer->step();
}

bool Actor::summon(int x, int y, UnitClass unitClass) {
    return composer->summon(x,y,unitClass);
}

std::vector<std::vector<FlyCell>> Actor::getFW() {
    return composer->getFW();
}

void Actor::exit() {
    composer->exit();

}

void Actor::restart() {
    composer->restart();


}

void Actor::setComposer(const std::shared_ptr<IFacade> &composer) {
    Actor::composer = composer;
}

//Actor::Actor(const std::shared_ptr<IFacade> &composerA) : composerA(composerA) {}

//Actor::Actor() {}

std::pair<int, std::pair<int, int>> Actor::getBaseStats(Devotion devotion) {
    return composer->getBaseStats(devotion);
}

Actor::Actor(const std::string &name) : name(name) {}

bool Actor::save(std::string fileName) {
    std::ofstream os(fileName);
    if(!os.is_open())return false;

    std::vector<std::vector<FlyCell>> vec;
    vec = getFW();
    os<<"{";
    for(const std::vector<FlyCell>& r:vec){
        os<<"{";
        for(FlyCell c:r){
            os<<"{";
            os<<"[";
            os<<int(c.getTerrain()->commonClass);
            os<<"][";
            auto ePtr = c.getEntity();
            if(ePtr) {
                os << int(ePtr->commonClass);
                os << "," <<ePtr->health;
                os << "," << ePtr->cur;
                os << "," << ePtr->lim;
            }
            os<<"][";
            auto uPtr = c.getUnit();
            if(uPtr) {
                os << int(c.getUnit()->commonClass);
                os << "," << c.getUnit()->health;
            }
            os<<"]";
            os<<"}";

        }
        os<<"}"<<std::endl;
    }
    os<<"}";
    os.close();
}
