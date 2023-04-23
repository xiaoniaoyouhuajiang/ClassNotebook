#ifndef OOP_FIELD_H
#define OOP_FIELD_H

#include <iostream>
#include <ctime>
#include <cstdlib>

#include "../Unit/Object/Object.h"
#include "Landscape/LandscapeFactory.h"
#include "../Unit/Object/ObjectFactory.h"
#include "Cell.h"
#include "../Interface/Logging/LogProxy.h"
#include "./FieldIterator.h"
#include "../Base/Base.h"
#include "../Interface/Snapshot/Snapshot.h"

/*
 * Field -- класс игрового поля.
 * -----------------------------------------------
 * objLimit, objCount -- лимит объектов на поле,
 * счетчик объектов на поле соответственно.
 * field -- двумерный массив клеток (класс Tile).
 * landscapeFactory -- фабрика типов ландшафта.
 * ----------------- Функции ---------------------
 * addObject -- добавление объекта на поле.
 * moveObject -- перемещение объекта по полю.
 * deleteObject -- удаление объекта с поля.
 * -----------------------------------------------
 */

class FieldIterator;
class Base;
class LogProxy;
class Snapshot;
class FieldIterator;
class Base;
class LogProxy;
class Snapshot;


class Field
{
    friend class FieldIterator;
    friend class Snapshot;

public:
    Field(int height, int width, int numberOfPlayers);
    ~Field();

    void addObject(Object* object, int x, int y);
    void moveObject(int x, int y, int i, int j);
    void makeDamage(int x, int y, int i, int j);
    void deleteObject(int x, int y);

    void createBase(int x, int y, int unitLimit, char id, int number);

    /* конструкторы копирования и перемещения */
    Field(const Field& other);
    Field(Field&& other);
    Field& operator=(const Field&);

    /* итератор поля */
    FieldIterator *iterator();
    FieldIterator *begin();
    FieldIterator *end();

    /* печать поля в консоль*/
    void show(char side);

    void getVision(char side, int x, int y);

    Snapshot* createSnapshot(std::string mode);

public:
    std::vector <Base*> basesOnField;
    Base* base;
    int height;
    int width;
    int objLimit;
    LogProxy* logging;
    Tile** field;
private:
    int objCount;
    LandscapeFactory landscapeFactory;
    ObjectFactory neutralFactory;
};



#endif //OOP_FIELD_H
