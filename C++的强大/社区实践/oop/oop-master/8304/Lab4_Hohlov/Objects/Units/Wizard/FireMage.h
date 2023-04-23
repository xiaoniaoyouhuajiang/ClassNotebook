
#ifndef UNTITLED13_FIREMAGE_H
#define UNTITLED13_FIREMAGE_H

#include "Wizard.h"
#include "../../../Weapon/Fireball.h"

class FireMage: public Wizard{

public:

    FireMage(): Wizard(*WeaponFlyWeight::getFlyWeight<Fireball>(), 100){}

};

#endif //UNTITLED13_FIREMAGE_H
