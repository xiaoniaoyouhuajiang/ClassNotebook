//
// Created by anton on 5/9/20.
//

#include "Unit.h"

#include "../../Mediator.h"
#include "../../Exeptions/BaseNotSetException.h"


Unit::Unit(int x, int y, Devotion devotion, CommonClass objectClass, int health, int armour, float dmgmul,
           int abPower, int abRange, int mbAgility, int mbRange, UnitType unitClass)
        : GameObject(x, y, false, devotion, ObjectType::Unit, objectClass, health, armour, dmgmul), ability(abPower,abRange,this),
          mobility(mbAgility,mbRange,this), unitClass(unitClass) {blocked=false;}

void Unit::act(std::shared_ptr<GameObject> obj) {
    //std::shared_ptr<Unit> unit = std::dynamic_pointer_cast<Unit>(obj);
    //if(unit){
    obj->getVitality().damage(this->ability.power);
    //}
}

void Unit::react(std::shared_ptr<GameObject> sbj) {

}

void Unit::step(std::shared_ptr<GameObject> obj) {
    //setCoords(obj->getCoords());
}

void Unit::restep(std::shared_ptr<GameObject> sbj) {

}

bool Unit::canStep(int x, int y) {
    return (getMobility().range>=getMediator()->distance() && !isBlocked());
}

bool Unit::canAct(int x, int y) {
    return getAbility().range>=getMediator()->distance();
}
/*
CommonClass Unit::getObjectClass() {
    return CommonClass::NONE;
}
*/
Ability &Unit::getAbility() {
    return ability;
}

Mobility &Unit::getMobility() {
    return mobility;
}

void Unit::setToBeRemoved(bool toBeRemoved) {
    try {
        if (!this->isToBeRemoved() && toBeRemoved) {
            this->toBeRemoved = toBeRemoved;
            notifyDeath();
        }
    }catch (BaseNotSetException& e){
        e.setDevotion(getDevotion());
        std::cerr<<e;
    }
}

void Unit::setBlocked(bool blocked) {
    Unit::blocked = blocked;
}

bool Unit::isBlocked() const {
    return blocked;
}
