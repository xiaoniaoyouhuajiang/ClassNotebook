//
// Created by Mila
//

#include <iostream>
#include "Archer.h"


Archer::Archer() : Artillerist() {
    Artillerist::health = 100;
    Artillerist::armor = 80;
    Artillerist::damage = 45;
    Artillerist::name = 'A';
}

void Archer::whatYouName() {
    std::cout<< name;
}

ObjectInterface *Archer::copy() {

    return new Archer(*this);

}


