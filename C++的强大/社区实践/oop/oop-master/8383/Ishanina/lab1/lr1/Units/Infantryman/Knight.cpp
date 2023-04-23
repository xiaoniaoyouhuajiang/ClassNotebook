//
// Created by Mila on 23.02.2020.
//

#include <iostream>
#include "Knight.h"

Knight::Knight(): Infantryman() {
    Infantryman::health = 150;
    Infantryman::armor = 50;
    Infantryman::damage = 35;
    Knight::name = 'K';
}

void Knight::whatYouName() {
    std::cout<< name;
}

ObjectInterface *Knight::copy() {
    return new Knight(*this);
}
