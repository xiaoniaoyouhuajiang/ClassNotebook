//
// Created by Alex on 08.03.2020.
//

#ifndef MYGAME_CAVALRYARMOR_H
#define MYGAME_CAVALRYARMOR_H


#include "../Armor.h"

class CavalryArmor: public Armor{
public:
    CavalryArmor();
    void upgradeArmor(int *money,int *costUpgrade,int *unitDamage, int *unitWeaponLevel) override;
};


#endif //MYGAME_CAVALRYARMOR_H
