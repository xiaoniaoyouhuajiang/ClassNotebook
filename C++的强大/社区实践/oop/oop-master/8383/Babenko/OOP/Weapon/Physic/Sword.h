#ifndef OOP_LAB1_SWORD_H
#define OOP_LAB1_SWORD_H

#include "../Weapon.h"

class Sword : public Weapon {
 public:
  Sword() {
    damage = 40;
    type = WeaponType::PHYSIC;
  }
};

#endif //OOP_LAB1_SWORD_H