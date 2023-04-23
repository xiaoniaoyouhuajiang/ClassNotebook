#ifndef OOP_LAB1_LAMINARARMOR_H
#define OOP_LAB1_LAMINARARMOR_H

#include "Armor.h"

class LaminarArmor : public Armor {

 public:
  LaminarArmor() {
    damageResistance = 10;
    type = ArmorType::MEDIUM;
  }
};

#endif //OOP_LAB1_LAMINARARMOR_H