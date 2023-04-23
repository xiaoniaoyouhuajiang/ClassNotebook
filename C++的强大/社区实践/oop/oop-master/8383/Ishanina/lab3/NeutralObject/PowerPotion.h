//
// Created by Mila
//

#ifndef UNTITLED_POWERPOTION_H
#define UNTITLED_POWERPOTION_H


#include "NeutralObject.h"

class PowerPotion: public NeutralObject {
public:
    PowerPotion();
    char whatYouName() override;
    NeutralObjectInterface* copy() override;
    bool canStepOnIt() override;
    void operator +(int* characteristic) override;

};


#endif //UNTITLED_POWERPOTION_H
