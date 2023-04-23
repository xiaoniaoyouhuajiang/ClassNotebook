//
// Created by Mila
//

#include "Stone.h"

Stone::Stone() {
    name = 'o';
}

char Stone::whatYouName() {
    return name;
}

NeutralObjectInterface *Stone::copy() {
    return new Stone(*this);
}

bool Stone::canStepOnIt() {// false т к на камень нельзя наступать
    return false;
}

void Stone::operator+(int *characteristic) {

}
