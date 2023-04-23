//
// Created by Alex on 16.02.2020.
//
#ifndef MYGAME_ARBALESTERS_H

#define MYGAME_ARBALESTERS_H


#include "LongRangeUnits.h"

class Arbalester : public LongRangeUnits {
public:
    Arbalester(int startX, int startY, Weapon*unitWeapon, Armor *unitArmor);
    Arbalester(const Arbalester &arbalester);
    Arbalester(Arbalester &&arbalesters);
    Arbalester &operator=(const Arbalester &arbalester) {
        if (&arbalester == this)
            return *this;

        delete unitPosition;
        unitPosition = new Position(0, 0);
        unitPosition->setNewPositionX(arbalester.unitPosition->getPositionX());
        unitPosition->setNewPositionY(arbalester.unitPosition->getPositionY());
        unitArmor = arbalester.unitArmor;
        unitWeapon = arbalester.unitWeapon;
        health = arbalester.getHealth();
        armor = arbalester.getArmor();
        damage = arbalester.getDamage();
        moves = arbalester.getMoves();
        numerInArmy = arbalester.getNumerInArmy();
        return *this;
    }
    Arbalester &operator=(Arbalester &&arbalester) {
        if (&arbalester == this)
            return *this;

        delete unitPosition;
        unitPosition = new Position(0, 0);
        unitPosition->setNewPositionX(arbalester.unitPosition->getPositionX());
        unitPosition->setNewPositionY(arbalester.unitPosition->getPositionY());
        unitArmor = arbalester.unitArmor;
        unitWeapon = arbalester.unitWeapon;
        health = arbalester.getHealth();
        armor = arbalester.getArmor();
        damage = arbalester.getDamage();
        moves = arbalester.getMoves();
        numerInArmy = arbalester.getNumerInArmy();
        arbalester.unitPosition = nullptr;
        return *this;
    }
    void attack() override;
};


#endif //MYGAME_ARBALESTERS_H
