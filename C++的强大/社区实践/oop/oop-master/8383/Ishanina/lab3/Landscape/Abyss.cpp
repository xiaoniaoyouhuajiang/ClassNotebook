//
// Created by Mila on 15.04.2020.
//

#include "Abyss.h"


//пропасть
Abyss::Abyss() {

    Landscape::name = '#';
}

char Abyss::whatYouName() {
    return name;
}

LandscapeInterface *Abyss::copy() {
    return new Abyss(*this);
}

void Abyss::updateUnitHealth(int* healthUnit) {
    *healthUnit = 0;
}

/*Abyss::~Abyss() {

}*/
