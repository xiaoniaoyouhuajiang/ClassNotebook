//
// Created by alexg on 03.06.2020.
//

#ifndef LABS_FACADE_H
#define LABS_FACADE_H

//#include "Field.h"
#include "ChainOfCommand.h"
#include "../extra4/adapter.h"

class Facade
{
private:
    Field *field;
    chainOfResponsibility *basecomm;
    Adapter* adapter;
public:
    Facade() {
        adapter = new Adapter();
    }

    void createField();
    void play();

    ~Facade() {
        delete adapter;
    }
};

#endif //LABS_FACADE_H
