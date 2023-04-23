//
// Created by shenk on 16.02.2020.
//

#ifndef UNTITLED13_ARCHER_H
#define UNTITLED13_ARCHER_H

#include "../../Weapon/Bow.h"
#include "../Unit.h"

class Archer: public Unit{

public:
    Archer(){

        weapon = Bow();

    }

};

#endif //UNTITLED13_ARCHER_H
