//
// Created by Mila
//

#include "MedicalKit.h"

MedicalKit::MedicalKit() {
    NeutralObject:: name = '+';
    NeutralObject:: bonus = 10;
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


