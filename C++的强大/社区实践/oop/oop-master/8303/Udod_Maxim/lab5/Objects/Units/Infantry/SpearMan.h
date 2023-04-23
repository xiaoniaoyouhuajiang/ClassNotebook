//
// Created by shenk on 16.02.2020.
//

#ifndef UNTITLED13_SPEARMAN_H
#define UNTITLED13_SPEARMAN_H

#include "Infantry.h"
#include "../../../Weapon/Spear.h"

class SpearMan: public Infantry{

public:

    SpearMan(): Infantry(*WeaponFlyWeight::getFlyWeight<Spear>(), 50){}

};

#endif //UNTITLED13_SPEARMAN_H
