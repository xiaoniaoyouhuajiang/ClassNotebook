//
// Created by Artem Butko on 08/05/2020.
//

#ifndef OOP_NEW_SHOOTER_H
#define OOP_NEW_SHOOTER_H

#include "../IUnit.h"

/*
 * Shooter -- обобщающий класс для юнитов-стрелков.
 */

class Shooter : public IUnit
{
public:
    Shooter(int health, int mana, int damage, int damageRange, int cost, int moveRange, char id);
    void regeneration(int health, int mana) override;
    void makeDamage(int damage, Object* other) override;
};


#endif //OOP_NEW_SHOOTER_H
