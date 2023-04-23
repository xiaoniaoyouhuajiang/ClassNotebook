#ifndef OOP_LAB1_LEATHERARMOR_H
#define OOP_LAB1_LEATHERARMOR_H

#include "Armor.h"

class LeatherArmor : public Armor {

 public:
  LeatherArmor() {
    damageResistance = 4;
    type = ArmorType::LIGHT;
  }

};

#endif //OOP_LAB1_LEATHERARMOR_H