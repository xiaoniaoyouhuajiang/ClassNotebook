#ifndef OOP1_FACTORYSOLDIER_H
#define OOP1_FACTORYSOLDIER_H

#include "FactoryUnit.h"
#include "OldSildier.h"
#include "YoungSoldier.h"

class FactorySoldier: FactoryUnit{
public:
    Unit* createStrongUnit() override {
        return new OldSoldier();
    }

    Unit* createWeakUnit() override {
        return  new YoungSoldier();
    }
};

#endif //OOP1_FACTORYSOLDIER_H
