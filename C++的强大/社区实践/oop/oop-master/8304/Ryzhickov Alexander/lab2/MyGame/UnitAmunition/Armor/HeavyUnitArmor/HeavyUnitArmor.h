//
// Created by Alex on 21.03.2020.
//

#ifndef GAME_HEAVYUNITARMOR_H
#define GAME_HEAVYUNITARMOR_H


#include "../Armor.h"

class HeavyUnitArmor : public Armor{
public:
    HeavyUnitArmor();
    void upgradeArmor(unsigned *level, unsigned *money,unsigned *damage) override;
};


#endif //GAME_HEAVYUNITARMOR_H
