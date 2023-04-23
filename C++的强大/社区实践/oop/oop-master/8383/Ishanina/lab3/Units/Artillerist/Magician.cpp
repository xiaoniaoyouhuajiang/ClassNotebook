//
// Created by Mila on 23.02.2020.
//

#include <iostream>
#include "Magician.h"
#include "../../Base/Base.h"


Magician::Magician() : Artillerist() {
    Artillerist::health = 100;
    Artillerist::armor = 75;
    Artillerist::damage = 50;
    Artillerist::name = 'M';
}

char Magician::whatYouName() {
    return name;

}

ObjectInterface *Magician::copy() {

    return new Magician(*this);

}

Magician::~Magician() {
    observer->handleEvent(numberInArray);

}

