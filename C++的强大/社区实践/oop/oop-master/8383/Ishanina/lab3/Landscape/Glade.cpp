//
// Created by Mila on 15.04.2020.
//

#include "Glade.h"

Glade::Glade() {
    Landscape::name = '*';
}

char Glade::whatYouName() {
    return name;
}

LandscapeInterface *Glade::copy() {
    return new Glade(*this);
}

void Glade::updateUnitHealth(int* healthUnit) {//////////////////////////////////////////
    //*healthUnit = *healthUnit;
}

/*Glade::~Glade() {

}*/
