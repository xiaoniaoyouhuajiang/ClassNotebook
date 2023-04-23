//
// Created by Alex on 21.03.2020.
//

#ifndef GAME_ATTACKUNITARMOR_H
#define GAME_ATTACKUNITARMOR_H


#include "../Armor.h"

class AttackUnitArmor : public Armor {
public:
    AttackUnitArmor();
    void upgradeArmor(unsigned *level, unsigned *money,unsigned *damage) override;
};


#endif //GAME_ATTACKUNITARMOR_H
