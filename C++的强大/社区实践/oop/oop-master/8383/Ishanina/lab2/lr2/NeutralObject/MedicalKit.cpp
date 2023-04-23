//
// Created by Mila
//

#include "MedicalKit.h"

MedicalKit::MedicalKit() {
    name = '+';
    bonus = 20;
}

char MedicalKit::whatYouName() {
    return name;
}

NeutralObjectInterface *MedicalKit::copy() {
    return new MedicalKit(*this);
}

bool MedicalKit::canStepOnIt() {
    return true;
}

void MedicalKit::operator+(int *characteristic) {
    *characteristic = *characteristic+bonus;
}
