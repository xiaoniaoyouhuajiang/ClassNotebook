//
// Created by anton on 2/12/20.
//

#ifndef PROJ_EPSILON_H
#define PROJ_EPSILON_H


#include "Mage.h"

class Epsilon : public Mage {
public:
    Epsilon(Field *fld, int x, int y, int health = 0, UnitDevotion devotion = UnitDevotion::NEUTER,
            bool active = false);

    wchar_t toChar() override;

    UnitClass getUnitClass() const override;

    int getPower() override;

    bool isValidStep(int x, int y) override;

    bool step(int x, int y) override;

    virtual GameObject &operator+=(const LandscapeProxy &b);

    GameObject &operator+=(const FieldCellProxy &b) override;

    GameObject &operator-=(const GameObject &b) override;

private:
    int ord;

};


#endif //PROJ_EPSILON_H
