//
// Created by anton on 5/25/20.
//

#include "AbstractUnitFactory.h"

#include "../../GameObject/Unit/Unit.h"
#include "../../Exeptions/AttemptToSetNeutralBaseException.h"

AbstractUnitFactory::AbstractUnitFactory(int health, int armour, float dmgmul, int abPower, int abRange, int mbAgility,
                                         int mbRange) : health(health), armour(armour), dmgmul(dmgmul),
                                                        abPower(abPower), abRange(abRange), mbAgility(mbAgility),
                                                        mbRange(mbRange) {}

void AbstractUnitFactory::setBase(std::shared_ptr<Base> base,Devotion devotion) {
    switch (devotion){

        case Devotion::Neuter:throw AttemptToSetNeutralBaseException("AbstractFactory");break;
        case Devotion::Light:this->lightBase=base;break;
        case Devotion::Dark:this->darkBase=base;break;
    }
    return;
}

void AbstractUnitFactory::onUnitCreate(std::shared_ptr<Unit> unit) {
    Devotion devotion=unit->getDevotion();
    switch(devotion){

        case Devotion::Neuter:break;
        case Devotion::Light:unit->setBase(lightBase);break;
        case Devotion::Dark:unit->setBase(darkBase);break;
    }
}
