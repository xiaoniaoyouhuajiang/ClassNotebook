//
// Created by Mila on 23.02.2020.
//

#include <iostream>
#include "Gnome.h"

Gnome::Gnome(): Infantryman() {
    Infantryman::health = 150;
    Infantryman::armor = 30;//т.к. гном, в отличие от рыцаря не в доспехах
    Infantryman::damage = 50;
    Infantryman::name = 'G';
}

void Gnome::whatYouName() {
    std::cout<< name;
}

ObjectInterface *Gnome::copy() {
    return new Gnome(*this);
}
