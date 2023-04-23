#ifndef OOP1_FACTORYTANKMAN_H
#define OOP1_FACTORYTANKMAN_H

#include "FactoryUnit.h"
#include "HeavyTankman.h"
#include "LightTankman.h"

class FactoryTankman: FactoryUnit{
public:
    Unit* createStrongUnit() override {
        return new HeavyTankman();
    }

    Unit* createWeakUnit() override {
        return  new LightTankman();
    }
};

#endif //OOP1_FACTORYTANKMAN_H
