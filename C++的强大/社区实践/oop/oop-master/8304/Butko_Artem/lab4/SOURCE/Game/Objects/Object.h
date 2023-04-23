//
// Created by Artem Butko on 08/05/2020.
//

#ifndef OOP_NEW_OBJECT_H
#define OOP_NEW_OBJECT_H

#include <iostream>
#include <cmath>
#include "Attributes/Damage/Damage.h"
#include "Attributes/Health/Health.h"
#include "Attributes/Mana/Mana.h"
#include "Attributes/Range/Range.h"
#include "Base/Subject/Subject.h"

/*
 * Object -- объединяющий класс атрибутов объекта.
 * -----------------------------------------------
 * damage -- очки урона, который может нанести
 * объект.
 * health -- очки здоровья объекта.
 * mana -- очки маны объекта.
 * range -- радиус перемещения юнита.
 * id -- идентификатор объекта (его имя).
 * x, y -- координаты нахождения объекта.
 */

class Object : public Subject
{
public:
    Damage damage;
    Health health;
    Mana mana;
    Range range;

    int x, y;
    char id;
    void death();

    virtual void getInformation();
};


#endif //OOP_NEW_OBJECT_H
