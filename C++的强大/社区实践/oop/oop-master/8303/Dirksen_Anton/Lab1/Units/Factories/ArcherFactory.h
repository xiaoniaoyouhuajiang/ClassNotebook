//
// Created by mensch on 15.03.2020.
//

#ifndef OOP_LABS_ARCHERFACTORY_H
#define OOP_LABS_ARCHERFACTORY_H


#include "UnitFactory.h"
#include "../Archers/Bowman.h"
#include "../Archers/Crossbowman.h"

class ArcherFactory : public UnitFactory {
public:
    Bowman* createCommon() override { return new Bowman();};
    Crossbowman* createStrong() override { return new Crossbowman();}
};


#endif //OOP_LABS_ARCHERFACTORY_H
