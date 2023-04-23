//
// Created by max on 19.02.20.
//

#ifndef OOP_INFANTRY_H
#define OOP_INFANTRY_H
#include "Unit.h"

class Infantry : public Unit{
public:
    Infantry()
    {

    }
    virtual string getUnitType() = 0;
};

class Spearman : public Infantry{
public:
    Spearman()
    {
        this->setParameters(10,4,3,"Spearsman");
        this->setMaxArmour(4);
    }
    int getMaxAttack() override;
    string getUnitType() override;
};

class Swordsman : public Infantry{
public:
    Swordsman()
    {
        this->setParameters(10,4,5,"Swordsman");
        this->setMaxArmour(4);
    }
    int getMaxAttack() override;
    string getUnitType() override;
};

#endif //OOP_INFANTRY_H
