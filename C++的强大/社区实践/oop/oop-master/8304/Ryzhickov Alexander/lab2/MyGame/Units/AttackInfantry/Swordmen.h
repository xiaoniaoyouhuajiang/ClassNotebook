//
// Created by Alex on 21.03.2020.
//

#ifndef GAME_SWORDMEN_H
#define GAME_SWORDMEN_H


#include "AttackInfantry.h"

class Swordmen: public AttackInfantry {
public:
    Swordmen(int startX, int startY, Weapon *unitWeapon, Armor *unitArmor);
    void attack(Unit *unit) override;

    //В первой лабораторной для всех юнитов были созданы
    //конструкторы и операторы копирования и перемещения
    //Это имело смысл потому, что у каждого юнита был собственный экземпляр оружия (UnitWeapon) и брони (UnitArmor)
    //Во второй лабораторной после применения паттерна "Компоновщик" конструкторы и операторы копирования и перемещения не нужны
    //Так как теперь у каждого юнита нет собственных экземпляров оружия (UnitWeapon) и брони (UnitArmor)

   /* Swordmen(const Swordmen &swordmen);
    Swordmen(Swordmen &&swordmen);

    Swordmen &operator=(const Swordmen &swordmen) {
        if (&swordmen == this)
            return *this;

        delete unitWeapon;
        delete unitArmor;
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

        delete unitWeapon;
        delete unitArmor;
        unitArmor = swordmen.unitArmor;
        unitWeapon = swordmen.unitWeapon;
        health = swordmen.getHealth();
        armor = swordmen.getArmor();
        damage = swordmen.getDamage();
        moves = swordmen.getMoves();
        numerInArmy = swordmen.getNumerInArmy();
        swordmen.unitWeapon = nullptr;
        swordmen.unitArmor = nullptr;
        return *this;
    }*/
};


#endif //GAME_SWORDMEN_H
