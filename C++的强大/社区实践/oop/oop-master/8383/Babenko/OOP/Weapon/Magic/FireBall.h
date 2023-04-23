#ifndef OOP_LAB1_FIREBALL_H
#define OOP_LAB1_FIREBALL_H
#include "../Weapon.h"

class Fireball : public Weapon {
 public:
  Fireball() {
    damage = 20;
    type = WeaponType::MAGIC;
  }
};

#endif //OOP_LAB1_FIREBALL_H