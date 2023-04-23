//
// Created by anton on 2/12/20.
//

#include "Gamma.h"

#include "../LandscapeProxy.h"

UnitClass Gamma::getUnitClass() const {
    return UnitClass::GAMMA;
}

bool Gamma::isAllyPowered() const {
    return Fighter::isAllyPowered();
}

void Gamma::setAllyPowered(bool allyPowered) {
    Fighter::setAllyPowered(allyPowered);
}

bool Gamma::isEnemyPowered() const {
    return Fighter::isEnemyPowered();
}

void Gamma::setEnemyPowered(bool enemyPowered) {
    Fighter::setEnemyPowered(enemyPowered);
}

bool Gamma::isValidStep(int x, int y) {
    return true;
}

wchar_t Gamma::toChar() {
    //return L'γ';
    return L'c';
}

bool Gamma::step(int x, int y) {
    if (isValidStep(x, y)) {
        GameObject::setCoords(x, y);
        return true;
    }
    return false;
}

Gamma::Gamma(Field *fld, int x, int y, int health, UnitDevotion devotion, bool active, bool allyPowered,
             bool enemyPowered) : Fighter(fld, x, y, health, devotion, active,
                                          allyPowered, enemyPowered), link(link) {
    /*TODO init link*/
    //link = new std::pair<int,int>(-1,-1);
}

GameObject &Gamma::operator+=(const LandscapeProxy &b) {
    return *this;
}

GameObject &Gamma::operator+=(const FieldCellProxy &b) {
    this->operator+=(b.getLandscape());
    GameObject* obj = b.getObject();
    if(obj->getUnitClass()==UnitClass::FIRE){
        die(*obj,*static_cast<GameObject*>(this));
        setActive(false);
        //mediator->destroyAt(x,y);
    }

    return *this;//TODO
}

GameObject &Gamma::operator-=(const GameObject &b) {
    return *this;//TODO
}

