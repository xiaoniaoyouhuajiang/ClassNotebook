//
// Created by max on 19.02.20.
//

#ifndef OOP_CAVALRY_H
#define OOP_CAVALRY_H

#include "Unit.h"

class Cavalry : public Unit{
public:
    Cavalry()
    {

    }
    virtual string getUnitType() = 0;
};

class LightCavalry : public Cavalry{
public:
    LightCavalry()
    {
        this->setParameters(10,4,4,"LightCavalry");
        this->setMaxArmour(4);
    }
    int getMaxAttack() override;
    string getUnitType() override;
};

class HardCavalry : public Cavalry{
public:
    HardCavalry()
    {
        this->setParameters(10,4,5,"HardCavalry");
        this->setMaxArmour(4);
    }
    int getMaxAttack() override;
     string getUnitType() override;
};


#endif //OOP_CAVALRY_H
