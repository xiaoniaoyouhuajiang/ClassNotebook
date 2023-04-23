//
// Created by Mila
//

#ifndef UNTITLED_MEDICALKIT_H
#define UNTITLED_MEDICALKIT_H


#include "NeutralObject.h"

class MedicalKit: public NeutralObject {
public:
    MedicalKit();
    char whatYouName() override;
    NeutralObjectInterface* copy() override;
    bool canStepOnIt() override;
    void operator +(int* characteristic) override;

};


#endif //UNTITLED_MEDICALKIT_H
