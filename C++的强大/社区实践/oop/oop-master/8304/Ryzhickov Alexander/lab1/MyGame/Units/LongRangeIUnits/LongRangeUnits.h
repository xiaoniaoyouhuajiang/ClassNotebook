//
// Created by Alex on 16.02.2020.
//

#ifndef MYGAME_LONGRANGEUNITS_H

#define MYGAME_LONGRANGEUNITS_H


#include "../Unit.h"

class LongRangeUnits : public Unit {
private:
    int countShots;
protected:
    void setCountShots(int countShots);

public:
    LongRangeUnits(int startX, int startY, Weapon*unitWeapon, Armor *unitArmor);
    LongRangeUnits();
};


#endif //MYGAME_LONGRANGEUNITS_H
