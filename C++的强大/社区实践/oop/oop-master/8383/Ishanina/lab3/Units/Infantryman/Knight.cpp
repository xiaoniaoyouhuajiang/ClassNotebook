//
// Created by Mila on 23.02.2020.
//

#include <iostream>
#include "Knight.h"
#include "../../Base/Base.h"

Knight::Knight(): Infantryman() {
    Infantryman::health = 150;
    Infantryman::armor = 50;
    Infantryman::damage = 35;
    Knight::name = 'K';
}

char Knight::whatYouName() {
    return name;
}

ObjectInterface *Knight::copy() {
    return new Knight(*this);
}

Knight::~Knight() {

    observer->handleEvent(numberInArray);

}