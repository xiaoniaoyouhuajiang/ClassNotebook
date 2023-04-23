//
// Created by shenk on 16.02.2020.
//

#ifndef UNTITLED13_FIREMAGE_H
#define UNTITLED13_FIREMAGE_H

#include "Wizard.h"
#include "../../Weapon/Fireball.h"

class FireMage: public Wizard{

public:

    FireMage(): Wizard(){

        weapon = Fireball();
        health = 100;

    }

};

#endif //UNTITLED13_FIREMAGE_H
