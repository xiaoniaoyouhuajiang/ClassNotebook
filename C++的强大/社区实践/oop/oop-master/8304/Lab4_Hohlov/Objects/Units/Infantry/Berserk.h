

#ifndef UNTITLED13_BERSERK_H
#define UNTITLED13_BERSERK_H

#include "Infantry.h"
#include "../../../Weapon/Axe.h"

class Berserk: public Infantry{

public:

    Berserk(): Infantry(*WeaponFlyWeight::getFlyWeight<Axe>(), 100){}

};

#endif //UNTITLED13_BERSERK_H
