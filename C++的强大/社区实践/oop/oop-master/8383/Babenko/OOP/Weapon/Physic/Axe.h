#ifndef OOP_LAB1_AXE_H
#define OOP_LAB1_AXE_H

#include "../Weapon.h"

class Axe : public Weapon {
 public:
  Axe() {
    damage = 50;
    type = WeaponType::PHYSIC;
  }
};

#endif //OOP_LAB1_AXE_H