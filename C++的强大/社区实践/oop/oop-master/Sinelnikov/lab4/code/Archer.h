//
// Created by max on 19.02.20.
//

#ifndef OOP_ARCHER_H
#define OOP_ARCHER_H

#include "Unit.h"

class Archer : public Unit {
public:
    Archer()
    {

    }
    virtual string getUnitType() = 0;
};

class Bowman : public Archer{
public:
    Bowman()
    {
        this->setParameters(10,3,3,"Bowman");
        this->setMaxArmour(3);
    }
    int getMaxAttack() override;
    string getUnitType() override;
};

class Crossbowman : public Archer{
public:
    Crossbowman()
    {
        this->setParameters(10,3,4,"Crossbowman");
        this->setMaxArmour(3);
    }
    int getMaxAttack() override;
    string getUnitType() override;
};

#endif //OOP_ARCHER_H
