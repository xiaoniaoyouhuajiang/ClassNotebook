//
// Created by anton on 2/18/20.
//

#ifndef PROJ_ZETA_H
#define PROJ_ZETA_H


#include "Fighter.h"

class Zeta : public Fighter {
public:
    Zeta(Field *fld, int x, int y, int health = 0, UnitDevotion devotion = UnitDevotion::NEUTER, bool active = false,
         bool allyPowered = false, bool enemyPowered = false);

    UnitClass getUnitClass() const override;

    bool isAllyPowered() const override;

    void setAllyPowered(bool allyPowered) override;

    bool isEnemyPowered() const override;

    void setEnemyPowered(bool enemyPowered) override;

    bool isValidStep(int x, int y) override;

    wchar_t toChar() override;

    bool step(int x, int y) override;

    virtual GameObject &operator+=(const LandscapeProxy &b);

    GameObject &operator+=(const FieldCellProxy &b) override;

    GameObject &operator-=(const GameObject &b) override;

};


#endif //PROJ_ZETA_H
