//
// Created by Mila
//

#include "Shild.h"

Shild::Shild() {
    NeutralObject:: name = '@';
    NeutralObject::bonus = 10;
}

char Shild::whatYouName() {
    return name;
}

NeutralObjectInterface *Shild::copy() {
    return new Shild(*this);
}

bool Shild::canStepOnIt() {
    return true;
}

void Shild::operator+(int *characteristic) {
    *characteristic = *characteristic+bonus;
}
