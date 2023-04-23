//
// Created by Alex on 16.02.2020.
//
#ifndef MYGAME_SPEARS_H

#define MYGAME_SPEARS_H


#include "Infantry.h"

class Spearmen: public Infantry{
public:
    Spearmen(int startX, int startY, Weapon*unitWeapon, Armor *unitArmor);
    Spearmen(const Spearmen &spearmen);
    Spearmen(Spearmen &&spearmen);
    Spearmen &operator=(const Spearmen &spearmen) {
        if (&spearmen == this)
            return *this;

        delete unitPosition;
        unitPosition = new Position(0, 0);
        unitPosition->setNewPositionX(spearmen.unitPosition->getPositionX());
        unitPosition->setNewPositionY(spearmen.unitPosition->getPositionY());
        unitArmor = spearmen.unitArmor;
        unitWeapon = spearmen.unitWeapon;
        health = spearmen.getHealth();
        armor = spearmen.getArmor();
        damage = spearmen.getDamage();
        moves = spearmen.getMoves();
        numerInArmy = spearmen.getNumerInArmy();
        return *this;
    }
    Spearmen &operator=(Spearmen &&spearmen) {
        if (&spearmen == this)
            return *this;

        delete unitPosition;
        unitPosition = new Position(0, 0);
        unitPosition->setNewPositionX(spearmen.unitPosition->getPositionX());
        unitPosition->setNewPositionY(spearmen.unitPosition->getPositionY());
        unitArmor = spearmen.unitArmor;
        unitWeapon = spearmen.unitWeapon;
        health = spearmen.getHealth();
        armor = spearmen.getArmor();
        damage = spearmen.getDamage();
        moves = spearmen.getMoves();
        numerInArmy = spearmen.getNumerInArmy();
        spearmen.unitPosition = nullptr;
        return *this;
    }
    void stronger() override;
    void attack() override;
};

#endif //MYGAME_SPEARS_H
