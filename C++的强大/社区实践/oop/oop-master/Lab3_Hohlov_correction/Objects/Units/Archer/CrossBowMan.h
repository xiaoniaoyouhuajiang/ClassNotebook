
#ifndef UNTITLED13_CROSSBOWMAN_H
#define UNTITLED13_CROSSBOWMAN_H

#include "Archer.h"
#include "../../../Armor/LeatherArmor.h"

class CrossBowMan: public Archer{

public:

    CrossBowMan(): Archer( *ArmorFlyWeight::getFlyWeight<LeatherArmor>(), 100){}

};

#endif //UNTITLED13_CROSSBOWMAN_H
