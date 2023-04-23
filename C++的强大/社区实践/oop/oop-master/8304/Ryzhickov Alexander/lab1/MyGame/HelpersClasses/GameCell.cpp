//
// Created by Alex on 02.03.2020.
//

#include "GameCell.h"

GameCell::GameCell() {
    GameCell::unit = nullptr;
    GameCell::neutralObject = nullptr;
    GameCell::base = nullptr;
    numer++;
}

void GameCell::setUnit(Unit *unit) {
    GameCell::unit = unit;
    if(neutralObject!= nullptr){
        neutralObject[unit->getDamage()];
    }
}

Unit *GameCell::getUnit() const {
    return unit;
}

void GameCell::deleteUnit() {
    GameCell::unit = nullptr;
}

void GameCell::setLanscape(Landscape *lanscape) {
    GameCell::lanscape = lanscape;
}

void GameCell::setNeutralObject(NeutralObject *neutralObject) {
    GameCell::neutralObject = neutralObject;
}

void GameCell::setBase(Base *base) {
    GameCell::base = base;
}
