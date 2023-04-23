#ifndef OOP_OBJECT_H
#define OOP_OBJECT_H

#include"../Attributes/Damage.h"
#include "../Attributes/Health.h"
#include "../Attributes/Mana.h"
#include "../Attributes/Range.h"
#include "../../Base/Subject.h"


class Object: public Subject
{
public:
    Damage damage;   //  урон
    Health health;  // здоровье
    Mana mana;     //  очки маны объекта
    Range range;  // радиус перемещения юнита

    int x, y;
    char id;          //  символ имени юнита
    void death();    //  функция при смерти
    char baseID;    //  ID принадлежаения базе
    virtual void getInformation();
};

#endif //OOP_OBJECT_H