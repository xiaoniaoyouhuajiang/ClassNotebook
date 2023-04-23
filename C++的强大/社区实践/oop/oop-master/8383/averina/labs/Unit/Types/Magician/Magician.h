#ifndef OOP_MAGICIAN_H
#define OOP_MAGICIAN_H

#include "../../Object/IUnit.h"


//  Magician - класс для юнитов-магов.


class Magician : public IUnit
{
public:
    Magician(int health, int mana, int damage, int damageRange, int cost, int moveRange, char id);
    void regeneration(int health, int mana) override;
    void makeDamage(int damage, Object* other) override;
};

#endif //OOP_MAGICIAN_H
