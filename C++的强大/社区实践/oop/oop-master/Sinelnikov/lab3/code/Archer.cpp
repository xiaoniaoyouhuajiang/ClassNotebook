//
// Created by max on 19.02.20.
//

#include "Archer.h"


int Bowman::getMaxAttack() {
    return 3;
}

int Crossbowman::getMaxAttack() {
    return 4;
}

string Bowman::getUnitType()  {
    return "Bowman";
}

string Crossbowman::getUnitType() {
    return "Crossbowman";
}