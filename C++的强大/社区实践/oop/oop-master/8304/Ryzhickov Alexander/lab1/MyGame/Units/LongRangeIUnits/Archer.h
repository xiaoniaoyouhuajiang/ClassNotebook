//
// Created by Alex on 16.02.2020.
//
#ifndef MYGAME_ARCHERS_H

#define MYGAME_ARCHERS_H


#include "LongRangeUnits.h"

class Archer : public LongRangeUnits {
public:
    Archer(int startX, int startY, Weapon *unitWeapon, Armor *unitArmor);

    Archer(const Archer &archer);

    Archer(Archer &&archers);
    Archer &operator=(const Archer &archer) {
        if (&archer == this)
            return *this;

        delete unitPosition;
        unitPosition = new Position(0, 0);
        unitPosition->setNewPositionX(archer.unitPosition->getPositionX());
        unitPosition->setNewPositionY(archer.unitPosition->getPositionY());
        unitArmor = archer.unitArmor;
        unitWeapon = archer.unitWeapon;
        health = archer.getHealth();
        armor = archer.getArmor();
        damage = archer.getDamage();
        moves = archer.getMoves();
        numerInArmy = archer.getNumerInArmy();
        return *this;
    }

    Archer &operator=( Archer &&archer) {
        if (&archer == this)
            return *this;

        delete unitPosition;
        unitPosition = new Position(0, 0);
        unitPosition->setNewPositionX(archer.unitPosition->getPositionX());
        unitPosition->setNewPositionY(archer.unitPosition->getPositionY());
        unitArmor = archer.unitArmor;
        unitWeapon = archer.unitWeapon;
        health = archer.getHealth();
        armor = archer.getArmor();
        damage = archer.getDamage();
        moves = archer.getMoves();
        numerInArmy = archer.getNumerInArmy();
        archer.unitPosition = nullptr;
        return *this;
    }

    void attack() override;
};


#endif //MYGAME_ARCHERS_H
