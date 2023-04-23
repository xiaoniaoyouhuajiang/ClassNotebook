
#ifndef OOP_WARRIOR_H
#define OOP_WARRIOR_H

#include "../../Object/IUnit.h"

// Обобщающий класс для юнитов-войнов.


class Warrior : public IUnit
{
public:
    Warrior(int health, int mana, int damage, int damageRange, int cost, int moveRange, char id);
    void regeneration(int health, int mana) override;
    void makeDamage(int damage, Object* other) override;
};


#endif //OOP_WARRIOR_H
