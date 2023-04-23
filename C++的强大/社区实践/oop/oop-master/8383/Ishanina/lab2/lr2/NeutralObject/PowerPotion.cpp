//
// Created by Mila
//

#include "PowerPotion.h"

PowerPotion::PowerPotion() {
    name = '&';
    bonus = 10;
}

char PowerPotion::whatYouName() {
    return name;
}

NeutralObjectInterface *PowerPotion::copy() {
    return new PowerPotion(*this);
}

bool PowerPotion::canStepOnIt() {
    return true;
}

void PowerPotion::operator+(int *characteristic) {
    *characteristic = *characteristic+bonus;
}

