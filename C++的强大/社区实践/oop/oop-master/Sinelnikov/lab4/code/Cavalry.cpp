//
// Created by max on 19.02.20.
//

#include "Cavalry.h"

int LightCavalry::getMaxAttack() {
    return 4;
}

int HardCavalry::getMaxAttack() {
    return 5;
}

string LightCavalry::getUnitType() {
    return "LightCavalry";
}

string HardCavalry::getUnitType() {
    return "HardCavalry";
}

