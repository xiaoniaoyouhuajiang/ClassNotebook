#ifndef OOP_IUNIT_H
#define OOP_IUNIT_H

#include "Object.h"


class IUnit : public Object
{
public:
//    функция воскрешения юнита.
    virtual void regeneration(int health, int mana) = 0;
//    функция нанесения урона другому юниту.
    virtual void makeDamage(int damage, Object* other) = 0;
};


#endif //OOP_IUNIT_H
