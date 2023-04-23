

#ifndef UNTITLED13_ARCHER_H
#define UNTITLED13_ARCHER_H

#include "../../../Weapon/Bow.h"
#include "../Unit.h"
#include "../../../Weapon/WeaponFlyWeight.h"
#include "../../../Armor/ArmorFlyWeight.h"

class Archer: public Unit{

public:
    Archer(Armor &armor, int health): Unit(UnitType::ARCHER, armor,*WeaponFlyWeight::getFlyWeight<Bow>(), health){}

};

#endif //UNTITLED13_ARCHER_H
