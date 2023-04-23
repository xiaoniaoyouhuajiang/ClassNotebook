

#ifndef UNTITLED13_StormMage_H
#define UNTITLED13_StormMage_H

#include "Wizard.h"
#include "../../../Weapon/Storm.h"

class StormMage: public Wizard{

public:

    StormMage(): Wizard(*WeaponFlyWeight::getFlyWeight<Storm>(), 7){}

};

#endif //UNTITLED13_StormMage_H
