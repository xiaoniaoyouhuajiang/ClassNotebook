#ifndef LABS_UNITFACTORY_H
#define LABS_UNITFACTORY_H

#include "UnitCreator.h"

class UnitFactory {
    NecroCreator necroCreator;
    PriestCreator priestCreator;
    YoyoCreator yoyoCreator;
    KatanaCreator katanaCreator;
    CrossbowCreator crossbowCreator;
    SlingermanCreator slingermanCreator;

public:
    UnitFactory();
    Unit* createUnit(char name, int x, int y);
};

#endif //LABS_UNITFACTORY_H
