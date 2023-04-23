//
// Created by Artem Butko on 08/05/2020.
//

#ifndef OOP_NEW_MAGICIAN_H
#define OOP_NEW_MAGICIAN_H

#include "../IUnit.h"

/*
 * Magician -- обобщающий класс для юнитов-магов.
 */

class Magician : public IUnit
{
public:
    Magician(int health, int mana, int damage, int damageRange, int cost, int moveRange, char id);
    void regeneration(int health, int mana) override;
    void makeDamage(int damage, Object* other) override;
};


#endif //OOP_NEW_MAGICIAN_H
