//
// Created by Alex on 21.03.2020.
//

#ifndef GAME_ARMOR_H
#define GAME_ARMOR_H


class Armor {
protected:
    unsigned baseArmor;
    unsigned cost;
    unsigned maxLevel;
    unsigned armorUpgradeValue;
public:
    virtual void upgradeArmor(unsigned *level, unsigned *money, unsigned *armor) = 0;

    unsigned int getBaseArmor() const;
};


#endif //GAME_ARMOR_H
