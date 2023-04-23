

#ifndef UNTITLED13_INFANTRY_H
#define UNTITLED13_INFANTRY_H

#include "../Unit.h"
#include "../../../Armor/ChainArmor.h"
#include "../../../Weapon/WeaponFlyWeight.h"
#include "../../../Armor/ArmorFlyWeight.h"

class Infantry: public Unit {

public:

    Infantry(Weapon &weapon, int health): Unit(UnitType::INFANTRY, *ArmorFlyWeight::getFlyWeight<ChainArmor>(), weapon, health) {}

};


#endif //UNTITLED13_INFANTRY_H
