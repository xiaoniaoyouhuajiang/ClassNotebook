//
// Created by shenk on 16.02.2020.
//

#ifndef UNTITLED13_SWORDMAN_H
#define UNTITLED13_SWORDMAN_H

#include "Infantry.h"
#include "../../Weapon/Sword.h"

class SwordMan: public Infantry{

public:

    SwordMan(): Infantry(){

        health = 100;
        weapon = Sword();

    }

};

#endif //UNTITLED13_SWORDMAN_H
