//
// Created by anton on 2/12/20.
//

#ifndef PROJ_BETA_H
#define PROJ_BETA_H


#include "God.h"
#include "../Base.h"


class Beta : public God {
private:
public:
    Beta(Field *fld, int x, int y, int health = 0, UnitDevotion devotion = UnitDevotion::NEUTER, bool active = false);

    //Beta(Field *fld, int x, int y, int health, UnitDevotion devotion, bool active, CommonFactory *factory,int unitLim);

    UnitClass getUnitClass() const override;

    void deathEvent() override;

    void summon(Direction dir) override;

    wchar_t toChar() override;

    bool isValidStep(int x, int y) override;

    bool step(int x, int y) override;

    virtual GameObject &operator+=(const LandscapeProxy &b);

    bool die(const GameObject &src, GameObject &dst) override;

    GameObject &operator+=(const FieldCellProxy &b) override;

    GameObject &operator-=(const GameObject &b) override;

//    void recieveDeath(GameObject *gameObject) override;


};


#endif //PROJ_BETA_H
