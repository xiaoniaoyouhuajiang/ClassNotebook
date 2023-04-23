//
// Created by anton on 2/12/20.
//

#ifndef PROJ_DELTA_H
#define PROJ_DELTA_H


#include "Mage.h"

class Delta : public Mage {
public:
    Delta(Field *fld, int x, int y, int health = 0, UnitDevotion devotion = UnitDevotion::NEUTER, bool active = false,
          int girdle = -1);

    GameObject &operator+=(const FieldCellProxy &b) override;

    GameObject &operator-=(const GameObject &b) override;

    virtual GameObject &operator+=(const LandscapeProxy &b);

private:
    wchar_t toChar() override;

    UnitClass getUnitClass() const override;

    int getPower() override;

    bool isValidStep(int x, int y) override;

    bool step(int x, int y) override;


private:
    int girdle;

};


#endif //PROJ_DELTA_H
