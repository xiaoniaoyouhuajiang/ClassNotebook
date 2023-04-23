//
// Created by Alex on 08.03.2020.
//

#ifndef MYGAME_LONGRANGEUNITSARMOR_H
#define MYGAME_LONGRANGEUNITSARMOR_H


#include "../Armor.h"

class LongRangeUnitsArmor: public Armor {
public:
    LongRangeUnitsArmor();
    void upgradeArmor(int *money,int *costUpgrade,int *unitDamage, int *unitWeaponLevel) override;
};


#endif //MYGAME_LONGRANGEUNITSARMOR_H
