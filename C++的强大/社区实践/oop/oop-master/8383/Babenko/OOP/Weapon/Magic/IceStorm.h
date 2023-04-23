#ifndef OOP_LAB1_ICESTORM_H
#define OOP_LAB1_ICESTORM_H

#include "../Weapon.h"

class IceStorm : public Weapon {
 public:
  IceStorm() {
    damage = 24;
    type = WeaponType::MAGIC;
  }
};

#endif //OOP_LAB1_ICESTORM_H