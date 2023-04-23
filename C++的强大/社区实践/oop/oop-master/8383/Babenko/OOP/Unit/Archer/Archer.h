#ifndef OOP_LAB1_ARCHER_H
#define OOP_LAB1_ARCHER_H

#include "../../Weapon/Far/Bow.h"
#include "../Unit.h"

class Archer : public Unit {

 public:
  Archer(Armor &armor, int health) : Unit(UnitType::ARCHER, armor, *WeaponFlyWeight::getFlyWeight<Bow>(), health) {}
};

#endif //OOP_LAB1_ARCHER_H