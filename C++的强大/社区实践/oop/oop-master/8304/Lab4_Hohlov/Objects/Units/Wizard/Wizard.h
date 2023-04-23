
#ifndef UNTITLED13_WIZARD_H
#define UNTITLED13_WIZARD_H

#include "../Unit.h"
#include "../../../Armor/Tunic.h"
#include "../../../Weapon/Fireball.h"
#include "../../../Weapon/WeaponFlyWeight.h"
#include "../../../Armor/ArmorFlyWeight.h"

class Wizard: public Unit{

public:

    Wizard(Weapon &weapon, int health): Unit(UnitType::WIZARD, *ArmorFlyWeight::getFlyWeight<Tunic>(), weapon, health){}

};

#endif //UNTITLED13_WIZARD_H
