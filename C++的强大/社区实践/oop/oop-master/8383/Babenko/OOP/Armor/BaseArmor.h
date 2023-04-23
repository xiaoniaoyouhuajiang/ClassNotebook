#ifndef INC_1_LAB_BASEARMOR_H
#define INC_1_LAB_BASEARMOR_H

#include "Armor.h"

class BaseArmor : public Armor {

 public:
  BaseArmor() {
    damageResistance = 200;
    type = ArmorType::BASE;
  }
};

#endif //INC_1_LAB_BASEARMOR_H
