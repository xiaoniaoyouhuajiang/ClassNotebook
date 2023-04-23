//
// Created by Mila on 16.04.2020.
//

#include "PowerPotion.h"

PowerPotion::PowerPotion() {

    NeutralObject:: name = '&';
    NeutralObject::bonus = 10;
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

