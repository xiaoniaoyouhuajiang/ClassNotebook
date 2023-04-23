//
// Created by Alex on 03.03.2020.
//

#include "UnitFactory.h"

UnitFactory::UnitFactory() {
    axe = new Axe();
    spear = new Spear();
    sword = new Sword();
    crossbow = new Crossbow();
    longBow = new LongBow();
    shortBow = new ShortBow();
    cavalryArmor = new CavalryArmor();
    infantryArmor = new InfantryArmor();
    longRangeUnitsArmor = new LongRangeUnitsArmor();
};

Swordmen *UnitFactory::getSwordsmen() {
    return new Swordmen(0, 0, sword, infantryArmor);
}

Spearmen *UnitFactory::getSpearmen() {
    return new Spearmen(0, 0, spear, infantryArmor);
}

LightCavalry *UnitFactory::getLightCavalry() {
    return new LightCavalry(0, 0, sword, cavalryArmor);
}

HeavyCavalry *UnitFactory::getHeavyCavalry() {
    return new HeavyCavalry(0, 0, spear, cavalryArmor);
}

Archer *UnitFactory::getArcherWithLongBow() {
    return new Archer(0, 0, longBow, longRangeUnitsArmor);
}

Archer *UnitFactory::getArcherWithShortBow() {
    return new Archer(0, 0, shortBow, longRangeUnitsArmor);
}

Arbalester *UnitFactory::getArbalester() {
    return new Arbalester(0, 0, crossbow, longRangeUnitsArmor);
}

UnitFactory::~UnitFactory() {
    delete axe;
    delete spear;
    delete sword;
    delete crossbow;
    delete longBow;
    delete shortBow;
    delete cavalryArmor;
    delete infantryArmor;
    delete longRangeUnitsArmor;
}

