//
// Created by Alex on 21.03.2020.
//

#ifndef GAME_WEAPON_H
#define GAME_WEAPON_H


class Weapon {
protected:
    unsigned baseDamage;
    unsigned cost;
    unsigned bonus;
    unsigned maxLevel;
    unsigned damageUpgradeValue;
public:
    virtual void upgradeWeapon(unsigned *level, unsigned *money,unsigned *damage) = 0;

    unsigned int getBaseDamage() const;

    unsigned int getCost() const;

    unsigned int getUpgradeBonus() const;
};


#endif //GAME_WEAPON_H
