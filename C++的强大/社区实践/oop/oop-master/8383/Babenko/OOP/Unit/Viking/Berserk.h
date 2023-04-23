#ifndef OOP_LAB1_BERSERK_H
#define OOP_LAB1_BERSERK_H

#include "Viking.h"
#include "../../Weapon/Physic/Axe.h"

class Berserk : public Viking {

 public:
  Berserk() : Viking(*WeaponFlyWeight::getFlyWeight<Axe>(), 60) {}
};

#endif //OOP_LAB1_BERSERK_H