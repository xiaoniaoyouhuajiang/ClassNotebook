//
// Created by Mila
//

#ifndef UNTITLED_STONE_H
#define UNTITLED_STONE_H


#include "NeutralObject.h"

class Stone: public NeutralObject {
public:
    Stone();
    char whatYouName() override;
    NeutralObjectInterface* copy() override;
    bool canStepOnIt() override;
    void operator +(int* characteristic) override;
};


#endif //UNTITLED_STONE_H
