#ifndef OOP_LAB1_VIKINGS_H
#define OOP_LAB1_VIKINGS_H

#include "../Unit.h"
#include "../../Armor/IronArmor.h"

class Viking : public Unit {

 public:
  Viking(Weapon &weapon, int health) : Unit(UnitType::VIKING,
                                            *ArmorFlyWeight::getFlyWeight<IronArmor>(),
                                            weapon,
                                            health) {}
};

#endif //OOP_LAB1_VIKINGS_H