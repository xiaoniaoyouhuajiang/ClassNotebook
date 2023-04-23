//
// Created by Alex on 21.03.2020.
//

#ifndef GAME_RANGEUNITARMOR_H
#define GAME_RANGEUNITARMOR_H


#include "../Armor.h"

class RangeUnitArmor : public Armor {
public:
    RangeUnitArmor();
    void upgradeArmor(unsigned *level, unsigned *money,unsigned *damage) override;
};


#endif //GAME_RANGEUNITARMOR_H
