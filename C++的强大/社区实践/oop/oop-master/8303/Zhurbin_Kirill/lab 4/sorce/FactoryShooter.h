#ifndef OOP1_FACTORYSHOOTER_H
#define OOP1_FACTORYSHOOTER_H

#include "FactoryUnit.h"
#include "KeenShooter.h"
#include "SlantingShooter.h"

class FactoryShooter: FactoryUnit{
public:
    Unit* createStrongUnit() override {
        return new KeenShooter();
    }

    Unit* createWeakUnit() override {
        return  new SlantingShooter();
    }
};

#endif //OOP1_FACTORYSHOOTER_H
