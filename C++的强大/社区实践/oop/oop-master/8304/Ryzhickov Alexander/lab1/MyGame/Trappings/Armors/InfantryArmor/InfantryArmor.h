//
// Created by Alex on 08.03.2020.
//

#ifndef MYGAME_INFANTRYARMOR_H
#define MYGAME_INFANTRYARMOR_H


#include "../Armor.h"

class InfantryArmor: public Armor {
public:
    InfantryArmor();
    void upgradeArmor(int *money,int *costUpgrade,int *unitDamage, int *unitWeaponLevel) override;
};


#endif //MYGAME_INFANTRYARMOR_H
