//
// Created by Mila
//

#include "Swamp.h"

Swamp::Swamp() {

    Landscape::name = '~';

}

char Swamp::whatYouName() {
    return name;
}

LandscapeInterface *Swamp::copy() {
    return new Swamp(*this);
}

void Swamp::updateUnitHealth(int* healthUnit) {//////////////////////////////////////
    *healthUnit = *healthUnit - 10;
}

//Swamp::~Swamp() {

//}
