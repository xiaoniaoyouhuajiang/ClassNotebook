#pragma once


#include "Mediator/concretemediator.h"


class Facade
{
public:
    ConcreteMediator* c;
    Facade(Game* game, int h, int w, bool* isUnitSelected, Object** selectedUnit, int* currNumBase){
        c = new ConcreteMediator(game, h, w, isUnitSelected, selectedUnit, currNumBase);
    }
    void func(){
        c->Notify();
    }
};
