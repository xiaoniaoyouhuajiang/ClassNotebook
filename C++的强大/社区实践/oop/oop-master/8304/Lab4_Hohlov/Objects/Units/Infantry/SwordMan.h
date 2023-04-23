

#ifndef UNTITLED13_SWORDMAN_H
#define UNTITLED13_SWORDMAN_H

#include "Infantry.h"
#include "../../../Weapon/Sword.h"

class SwordMan: public Infantry{

public:

    SwordMan(): Infantry(*WeaponFlyWeight::getFlyWeight<Sword>(), 50){}

};

#endif //UNTITLED13_SWORDMAN_H
