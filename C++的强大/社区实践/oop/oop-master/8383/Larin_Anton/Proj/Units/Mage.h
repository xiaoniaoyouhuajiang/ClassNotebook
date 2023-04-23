//
// Created by anton on 2/12/20.
//

#ifndef PROJ_MAGE_H
#define PROJ_MAGE_H


#include "../GameObject.h"

class Mage : public GameObject {
private:

public:
    Mage(Field *fld, int x, int y, int health, UnitDevotion devotion, bool active);

    virtual int getPower();

    virtual bool isValidStep(int x, int y) = 0;

    virtual bool step(int x, int y) = 0;

    //virtual UnitDevotion getUnitDevotion() override;
};


#endif //PROJ_MAGE_H
