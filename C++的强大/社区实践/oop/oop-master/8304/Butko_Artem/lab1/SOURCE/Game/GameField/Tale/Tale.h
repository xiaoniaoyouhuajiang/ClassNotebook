//
// Created by Artem Butko on 14/05/2020.
//

#ifndef OOP_NEW_TALE_H
#define OOP_NEW_TALE_H

#include "../../Objects/Object.h"

/*
 * Tale -- класс клетки игрового поля.
 * -----------------------------------------------
 * object -- объект, который находится на клетке игрового поля.
 * x, y -- координаты нахождения.
 */

class Tale
{
public:
    Tale() = default;
    ~Tale() = default;
    Object *object;
    int x, y;
};


#endif //OOP_NEW_TALE_H
