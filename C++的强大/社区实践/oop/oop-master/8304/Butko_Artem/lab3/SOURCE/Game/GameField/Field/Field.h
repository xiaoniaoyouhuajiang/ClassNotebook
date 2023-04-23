//
// Created by Artem Butko on 14/05/2020.
//

#ifndef OOP_NEW_FIELD_H
#define OOP_NEW_FIELD_H

#include <iostream>
#include <ctime>
#include <cstdlib>
#include "../Tale/Tale.h"
#include "Iterator/FieldIterator.h"
#include "../../Factories/LandscapeFactory/LandscapeFactory.h"
#include "../../Objects/Base/Base.h"

/*
 * Field -- класс игрового поля.
 * -----------------------------------------------
 * objLimit, objCount -- лимит объектов на поле,
 * счетчик объектов на поле соответственно.
 * field -- двумерный массив клеток (класс Tale).
 * landscapeFactory -- фабрика типов ландшафта.
 * ----------------- Функции ---------------------
 * addObject -- добавление объекта на поле.
 * moveObject -- перемещение объекта по полю.
 * deleteObject -- удаление объекта с поля.
 * -----------------------------------------------
 */


class FieldIterator;
class Base;

class Field
{
    friend FieldIterator;
public:
    Field(int height, int width);
    ~Field();

    int addObject(Object* object, int x, int y);
    int moveObject(int x, int y, int i, int j);
    int deleteObject(int x, int y);
    void makeDamage(int x, int y, int i, int j);

    int createBase(int x, int y, int unitLimit);

    /* конструкторы копирования и перемещения */
    Field(const Field& other);
    Field(Field&& other);

    /* итератор поля */
    FieldIterator *iterator();
    FieldIterator *begin();
    FieldIterator *end();

    /* печать поля в консоль*/
    void show();

    /* мгновенная смерть */
    void immediateDeath(int x, int y);

    Base* base;
private:
    int height;
    int width;
    int objLimit;
    int objCount;

    Tale** field;
    LandscapeFactory landscapeFactory;
    ObjectFactory neutralFactory;
};


#endif //OOP_NEW_FIELD_H
