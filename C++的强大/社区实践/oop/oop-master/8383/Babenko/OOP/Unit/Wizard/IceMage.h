#ifndef OOP_LAB1_ICEMAGE_H
#define OOP_LAB1_ICEMAGE_H

#include "Wizard.h"
#include "../../Weapon/Magic/IceStorm.h"

class IceMage : public Wizard {
 public:
  IceMage() : Wizard(*WeaponFlyWeight::getFlyWeight<IceStorm>(), 90) {}
};

#endif //OOP_LAB1_ICEMAGE_H