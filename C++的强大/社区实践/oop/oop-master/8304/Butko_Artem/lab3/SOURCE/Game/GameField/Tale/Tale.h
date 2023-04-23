//
// Created by Artem Butko on 14/05/2020.
//

#ifndef OOP_NEW_TALE_H
#define OOP_NEW_TALE_H

#include "../../Objects/Object.h"
#include "../../Landscape/ILandscape.h"
#include "../../Objects/Neutral/INeutral.h"

/*
 * Tale -- класс клетки игрового поля.
 * -----------------------------------------------
 * object -- объект, который находится на клетке игрового поля.
 * landscape -- тип ландшафта на клетке.
 * x, y -- координаты нахождения.
 */

class Tale
{
public:
    Tale() = default;
    ~Tale() = default;

    Object* object;
    INeutral* neutral;
    ILandscape* landscape;
    int x, y;
};


#endif //OOP_NEW_TALE_H
