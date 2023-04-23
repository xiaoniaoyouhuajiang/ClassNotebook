//
// Created by Mila
//

#ifndef UNTITLED_NEUTRALOBJECT_H
#define UNTITLED_NEUTRALOBJECT_H


#include "NeutralObjectInterface.h"

class NeutralObject : public NeutralObjectInterface{

public:
    char whatYouName() override = 0; //
    NeutralObjectInterface* copy() override = 0;
    bool canStepOnIt() override = 0;
    void operator +(int* characteristic) override = 0;

protected:
    char name;
    int bonus;
};


#endif //UNTITLED_NEUTRALOBJECT_H
