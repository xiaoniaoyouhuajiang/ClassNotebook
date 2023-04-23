//
// Created by Alex on 21.03.2020.
//

#include <iostream>
#include "Base.h"
#include "../Field/Field.h"

Base::Base(Unit **units, int x, int y, int maxCountUnitsInGame, Field *field, int health, int money) : yPosition(y), xPosition(x),
                                                                                maxCountUnitsInGame(
                                                                                        maxCountUnitsInGame),
                                                                                maxCountUnitsOnBase(10) {
    Base::countUnitsOnBase = 0;
    Base::countUnitsInGame = 0;
    Base::healthBase = health;
    Base::money = money;
    Base::units = units;
    Base::factory = new UnitFactory;
    Base::vectorDeleteUnits.reserve(maxCountUnitsInGame);
    Base::field = field;

    // Моделируем создание юнитов и их смерть
    /* addSwordsmen();
     delete(units[0]);
     addSwordsmen();
     addSwordsmen();
     addKing();*/

    /*   addArcher(0, 0);
       addKing(1, 0);
       addKnight(0, 1);
       addMagician(1, 2);
       addSpearmen(2, 1);
       addSwordsmen(2, 2);*/

//    std::cout << "dfsd\n";
}

void Base::addUnit(int x, int y, Unit *unit) {
    if (field->getCell(x, y)->getUnit() == nullptr) {
        if (vectorDeleteUnits.empty()) {
            units[countUnitsOnBase] = unit;
            units[countUnitsOnBase]->setNumerInArmy(countUnitsOnBase);
            units[countUnitsOnBase]->add(this);
            units[countUnitsOnBase]->setMoney(&money);
            countUnitsOnBase++;
            countUnitsInGame++;
        } else {
            units[vectorDeleteUnits.front()] = unit;
            units[vectorDeleteUnits.front()]->setNumerInArmy(vectorDeleteUnits.front());
            units[vectorDeleteUnits.front()]->add(this);
            units[vectorDeleteUnits.front()]->setMoney(&money);
            vectorDeleteUnits.erase(vectorDeleteUnits.begin());
            countUnitsInGame++;
        }
        field->setUnit(x, y, unit);
    }
}

void Base::addSwordsmen(int x, int y) {
    addUnit(x, y, factory->getSwordsmen(x, y));
}

void Base::addSpearmen(int x, int y) {
    addUnit(x, y, factory->getSpearmen(x, y));

}

void Base::addArcher(int x, int y) {
    addUnit(x, y, factory->getArcher(x, y));

}

void Base::addMagician(int x, int y) {
    addUnit(x, y, factory->getMagician(x, y));

}

void Base::addKing(int x, int y) {
    addUnit(x, y, factory->getKing(x, y));

}

void Base::addKnight(int x, int y) {
    addUnit(x, y, factory->getKnight(x, y));

}

void Base::handleEvent(const Unit &unit) {
    //std::cout << unit.getNumerInArmy() << "\n";
    vectorDeleteUnits.emplace_back(unit.getNumerInArmy());
    countUnitsInGame--;
}

Base::~Base() {
    delete (factory);
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

int Base::getHealthBase() const {
    return healthBase;
}

int Base::getCountUnitsOnBase() const {
    return countUnitsOnBase;
}

int Base::getMoney() const {
    return money;
}

void Base::loadSworsmen(int startX, int startY, int numberInArray, int health,
                        int armor, int damage, int attackBonus) {
    addUnit(startX, startY, factory->loadSwordsmen(startX, startY, numberInArray, health, armor, damage, attackBonus));
}

void Base::loadSpearmen(int startX, int startY, int numberInArray, int health,
                        int armor, int damage, int attackBonus) {
    addUnit(startX, startY, factory->loadSpearmen(startX, startY, numberInArray, health, armor, damage, attackBonus));
}

void
Base::loadArcher(int startX, int startY, int numberInArray, int health, int armor,
                 int damage, int attackBonus) {
    addUnit(startX, startY, factory->loadArcher(startX, startY, numberInArray, health, armor, damage, attackBonus));
}

void Base::loadMagician(int startX, int startY, int numberInArray, int health,
                        int armor, int damage, int attackBonus) {
    addUnit(startX, startY, factory->loadMagician(startX, startY, numberInArray, health, armor, damage, attackBonus));
}

void
Base::loadKing(int startX, int startY, int numberInArray, int health, int armor,
               int damage, int attackBonus) {
    addUnit(startX, startY, factory->loadKing(startX, startY, numberInArray, health, armor, damage, attackBonus));
}

void
Base::loadKnight(int startX, int startY, int numberInArray, int health, int armor,
                 int damage, int attackBonus) {
    addUnit(startX, startY, factory->loadKnight(startX, startY, numberInArray, health, armor, damage, attackBonus));
}

int Base::getCountUnits() {
    return countUnitsInGame + vectorDeleteUnits.size();
}

std::string Base::getInformationAboutBase() {
    std::string inf = "Base\n";
    inf.append("x : " + std::to_string(xPosition) + '\n');
    inf.append("y : " + std::to_string(yPosition) + '\n');
    inf.append("maxCountUnit : " + std::to_string(maxCountUnitsInGame) + '\n');
    inf.append("health : " + std::to_string(healthBase) + '\n');
    inf.append("money : " + std::to_string(money) + '\n');

    return inf;
}

int *Base::getMoneyAdresse() {
    return &money;
}

