//
// Created by Alex on 08.03.2020.
//

#ifndef MYGAME_ARMOR_H
#define MYGAME_ARMOR_H


class Armor {
protected:
    int armor;
    int level;
    int cost;
public:
    Armor();
    int getArmor() const;
    virtual void upgradeArmor(int *money,int *costUpgrade,int *unitDamage, int *unitWeaponLevel) = 0;
};


#endif //MYGAME_ARMOR_H
