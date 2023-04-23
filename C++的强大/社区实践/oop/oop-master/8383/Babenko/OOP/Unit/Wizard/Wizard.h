#ifndef OOP_LAB1_WIZARD_H
#define OOP_LAB1_WIZARD_H

#include "../Unit.h"
#include "../../Armor/Cape.h"
#include "../../Weapon/Magic/FireBall.h"

class Wizard : public Unit {

 public:
  Wizard(Weapon &weapon, int health) : Unit(UnitType::WIZARD,
                                            *ArmorFlyWeight::getFlyWeight<Cape>(),
                                            weapon,
                                            health) {}
};

#endif //OOP_LAB1_WIZARD_H