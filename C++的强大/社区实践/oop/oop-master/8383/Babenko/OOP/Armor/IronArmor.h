#ifndef OOP_LAB1_IRONARMOR_H
#define OOP_LAB1_IRONARMOR_H

#include "Armor.h"

class IronArmor : public Armor {

 public:
  IronArmor() {
    damageResistance = 60;
    type = ArmorType::HEAVY;
  }
};

#endif //OOP_LAB1_IRONARMOR_H