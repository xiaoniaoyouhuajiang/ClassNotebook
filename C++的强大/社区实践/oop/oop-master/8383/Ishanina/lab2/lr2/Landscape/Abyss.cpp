//
// Created by Mila
//

#include "Abyss.h"
//пропасть

Abyss::Abyss() {
    name = '#';
}

char Abyss::whatYouName() {
    return name;
}

LandscapeInterface *Abyss::copy() {
    return new Abyss(*this);
}

void Abyss::updateUnitHealth(int* healthUnit, char nameUnit) {
    *healthUnit = 0;
}


