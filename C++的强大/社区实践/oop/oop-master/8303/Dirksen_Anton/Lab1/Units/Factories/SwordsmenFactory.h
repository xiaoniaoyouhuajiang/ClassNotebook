//
// Created by mensch on 15.03.2020.
//

#ifndef OOP_LABS_SWORDSMENFACTORY_H
#define OOP_LABS_SWORDSMENFACTORY_H


#include "UnitFactory.h"
#include "../Swordsmen/Knight.h"
#include "../Swordsmen/Squire.h"

class SwordsmenFactory : public UnitFactory{
public:
    Squire* createCommon() override {return new Squire;}
    Knight* createStrong() override {return new Knight;}
};


#endif //OOP_LABS_SWORDSMENFACTORY_H
