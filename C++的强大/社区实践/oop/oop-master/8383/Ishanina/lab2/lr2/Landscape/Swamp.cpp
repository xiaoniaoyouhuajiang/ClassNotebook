//
// Created by Mila
//

#include "Swamp.h"

Swamp::Swamp() {
    name = '~';
}

char Swamp::whatYouName() {
    return name;
}

LandscapeInterface *Swamp::copy() {
    return new Swamp(*this);
}

void Swamp::updateUnitHealth(int* healthUnit, char nameUnit) {
    *healthUnit = *healthUnit - 10;
}


