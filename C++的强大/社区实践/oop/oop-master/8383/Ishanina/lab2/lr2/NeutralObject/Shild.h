//
// Created by Mila
//

#ifndef UNTITLED_SHILD_H
#define UNTITLED_SHILD_H


#include "NeutralObject.h"

class Shild : public NeutralObject {//щит

public:
    Shild();
    char whatYouName() override;
    NeutralObjectInterface* copy() override;
    bool canStepOnIt() override;
    void operator +(int* characteristic) override;

};


#endif //UNTITLED_SHILD_H
