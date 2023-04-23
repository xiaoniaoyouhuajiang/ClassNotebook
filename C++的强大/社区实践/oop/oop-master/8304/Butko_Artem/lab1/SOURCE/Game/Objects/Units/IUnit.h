//
// Created by Artem Butko on 08/05/2020.
//

#ifndef OOP_NEW_IUNIT_H
#define OOP_NEW_IUNIT_H

#include "../Object.h"

/*
 * IUnit -- класс-интерфейс для юнитов.
 * -------------------------------------
 * regeneration -- ф-ция регенерации юнита.
 * makeDamage -- ф-ция нанесения урона дру-
 * гому юниту.
 */

class IUnit : public Object
{
public:
    virtual void regeneration(int health, int mana) = 0;
    virtual void makeDamage(int damage, Object* other) = 0;
};

#endif //OOP_NEW_IUNIT_H
