//
// Created by shenk on 16.02.2020.
//

#ifndef UNTITLED13_WIZARD_H
#define UNTITLED13_WIZARD_H

#include "../Unit.h"
#include "../../Armor/Tunic.h"
#include "../../Weapon/Fireball.h"

class Wizard: public Unit{

public:

    Wizard(){

        armor = Tunic();

    }

};

#endif //UNTITLED13_WIZARD_H
