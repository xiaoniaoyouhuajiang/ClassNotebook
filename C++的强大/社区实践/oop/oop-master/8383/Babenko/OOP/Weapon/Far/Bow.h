#ifndef OOP_LAB1_BOW_H
#define OOP_LAB1_BOW_H

#include "../Weapon.h"

class Bow : public Weapon {
 public:
  Bow() {
    damage = 10;
    type = WeaponType::FAR;
  }
};

#endif //OOP_LAB1_BOW_H