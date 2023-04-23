#ifndef OOP_LAB1_SWORDMAN_H
#define OOP_LAB1_SWORDMAN_H

#include "Viking.h"
#include "../../Weapon/Physic/Sword.h"

class SwordMan : public Viking {

 public:
  SwordMan() : Viking(*WeaponFlyWeight::getFlyWeight<Sword>(), 100) {}
};
#endif //OOP_LAB1_SWORDMAN_H