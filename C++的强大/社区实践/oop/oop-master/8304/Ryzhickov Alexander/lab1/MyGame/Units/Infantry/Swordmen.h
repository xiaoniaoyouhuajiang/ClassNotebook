//
// Created by Alex on 16.02.2020.
//
#ifndef MYGAME_SWORDSMEN_H

#define MYGAME_SWORDSMEN_H


#include "Infantry.h"

class Swordmen : public Infantry {
public:
    Swordmen(int startX, int startY, Weapon *unitWeapon, Armor *unitArmor);

    Swordmen(const Swordmen &swordmen);

    Swordmen(Swordmen &&swordmen);

    Swordmen &operator=(const Swordmen &swordmen) {
        if (&swordmen == this)
            return *this;

        delete unitPosition;
        unitPosition = new Position(0, 0);
        unitPosition->setNewPositionX(swordmen.unitPosition->getPositionX());
        unitPosition->setNewPositionY(swordmen.unitPosition->getPositionY());
        unitArmor = swordmen.unitArmor;
        unitWeapon = swordmen.unitWeapon;
        health = swordmen.getHealth();
        armor = swordmen.getArmor();
        damage = swordmen.getDamage();
        moves = swordmen.getMoves();
        numerInArmy = swordmen.getNumerInArmy();
        return *this;
    }

    Swordmen &operator=(Swordmen &&swordmen) {
        if (&swordmen == this)
            return *this;

        delete unitPosition;
        unitPosition = new Position(0, 0);
        unitPosition->setNewPositionX(swordmen.unitPosition->getPositionX());
        unitPosition->setNewPositionY(swordmen.unitPosition->getPositionY());
        unitArmor = swordmen.unitArmor;
        unitWeapon = swordmen.unitWeapon;
        health = swordmen.getHealth();
        armor = swordmen.getArmor();
        damage = swordmen.getDamage();
        moves = swordmen.getMoves();
        numerInArmy = swordmen.getNumerInArmy();
        swordmen.unitPosition = nullptr;
        return *this;
    }

    void stronger() override;

    void attack() override;


};


#endif //MYGAME_SWORDSMEN_H
