//
// Created by Mila
//

#include "Glade.h"

Glade::Glade() {
    name = '*';
}

char Glade::whatYouName() {
    return name;
}

LandscapeInterface *Glade::copy() {
    return new Glade(*this);
}

void Glade::updateUnitHealth(int* healthUnit, char nameUnit) {

}


