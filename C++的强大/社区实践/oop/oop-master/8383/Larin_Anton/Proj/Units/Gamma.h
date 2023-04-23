//
// Created by anton on 2/12/20.
//

#ifndef PROJ_GAMMA_H
#define PROJ_GAMMA_H


#include <utility>
#include "Fighter.h"

#include "../FieldCellProxy.h"

class Gamma : public Fighter {
private:
    std::pair<int, int> link;
public:
    Gamma(Field *fld, int x, int y, int health = 0, UnitDevotion devotion = UnitDevotion::NEUTER, bool active = false,
          bool allyPowered = false, bool enemyPowered = false);

    std::pair<int, int> *getIntersects(int &amount);

    bool ritual();

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


#endif //PROJ_GAMMA_H
