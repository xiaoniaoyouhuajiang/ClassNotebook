//
// Created by Alex on 05.03.2020.
//

#include <iostream>
#include "Base.h"


Base::Base(Unit **units, int x,int y, int maxCountUnitsInGame) : yPosition(y), xPosition(x), maxCountUnitsInGame(maxCountUnitsInGame),
                                                                 maxCountUnitsOnBase(10) {
    Base::countUnitsOnBase = 0;
    Base::countUnitsInGame = 0;
    Base::healthBase = 1000;
    Base::money = 1000;
    Base::units = units;
    Base::factory = new UnitFactory;
    Base::vectorDeleteUnits.reserve(maxCountUnitsInGame);

    addArbalester();
    delete(units[0]);
    addArbalester();
    addArbalester();
}

void Base::addUnit(Unit *unit) {
    if(vectorDeleteUnits.empty()) {
        units[countUnitsOnBase] = unit;
        units[countUnitsOnBase]->setNumerInArmy(countUnitsOnBase);
        units[countUnitsOnBase]->add(this);
        countUnitsOnBase++;
        countUnitsInGame++;
    } else{
        units[vectorDeleteUnits.front()] = unit;
        units[vectorDeleteUnits.front()]->setNumerInArmy(vectorDeleteUnits.front());
        units[vectorDeleteUnits.front()]->add(this);
        vectorDeleteUnits.erase(vectorDeleteUnits.begin());
        countUnitsInGame++;
    }
}

void Base::addSwordsmen() {
    addUnit(factory->getSwordsmen());

}

void Base::addSpearmen() {
    addUnit(factory->getSpearmen());

}

void Base::addArcherWithShortBow() {
    addUnit(factory->getArcherWithShortBow());

}

void Base::addArcherWithLongBow() {
    addUnit(factory->getArcherWithLongBow());

}

void Base::addArbalester()  {
    addUnit(factory->getArbalester());

}

void Base::addHeavyCavalry() {
    addUnit(factory->getHeavyCavalry());

}

void Base::addLightCavalry() {
    addUnit(factory->getLightCavalry());

}

void Base::handleEvent(const Unit& unit) {
   // std::cout << "!";
    std::cout << unit.getNumerInArmy() << " ";
    vectorDeleteUnits.emplace_back(unit.getNumerInArmy());
    //countUnitsOnBase--;
    countUnitsInGame--;
}

Base::~Base() {
    delete(factory);
}

int Base::getCountUnitsInGame() const {
    return countUnitsInGame;
}

const int Base::getXPosition() const {
    return xPosition;
}

const int Base::getYPosition() const {
    return yPosition;
}
