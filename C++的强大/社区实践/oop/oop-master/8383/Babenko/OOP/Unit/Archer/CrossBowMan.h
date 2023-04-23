#ifndef OOP_LAB1_CROSSBOWMAN_H
#define OOP_LAB1_CROSSBOWMAN_H
#include "Archer.h"
#include "../../Armor/LaminarArmor.h"

class CrossBowMan : public Archer {

 public:
  CrossBowMan() : Archer(*ArmorFlyWeight::getFlyWeight<LaminarArmor>(), 110) {}
};
#endif //OOP_LAB1_CROSSBOWMAN_H