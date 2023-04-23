//
// Created by max on 01.04.20.
//

#ifndef OOP_BASEACTION_H
#define OOP_BASEACTION_H


#include "Field.h"
#include "Base.h"
#include "Interaction.h"

class BaseAction {
public:
    BaseAction()
    {

    }
    ~BaseAction()
    {

    }
    void run(Field* f,bool &check);
    void showCharacteristics(Field* f,Base* base);
    void setBase(Field* f);
};


#endif //OOP_BASEACTION_H
