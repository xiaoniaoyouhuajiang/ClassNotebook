//
// Created by max on 19.02.20.
//

#include "Infantry.h"

int Spearman::getMaxAttack() {
    return 3;
}

int Swordsman::getMaxAttack() {
    return 5;
}

string Spearman::getUnitType() {
    return "Spearman";
}

string Swordsman::getUnitType() {
    return "Swordsman";
}

