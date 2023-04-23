//
// Created by Alex on 21.03.2020.
//

#ifndef GAME_SPEARMEN_H
#define GAME_SPEARMEN_H


#include "AttackInfantry.h"
namespace GameUnit {
    class Spearmen : public AttackInfantry {
    public:
        Spearmen(int startX, int startY, Weapon *unitWeapon, Armor *unitArmor);

        Spearmen(int startX, int startY, Weapon *unitWeapon, Armor *unitArmor, int numberInArray, int health, int armor,
                 int damage, int attackBonus);

        void attack(Unit *unit) override;
    };
}

#endif //GAME_SPEARMEN_H
