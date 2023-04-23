//
// Created by Artem Butko on 14/05/2020.
//

#ifndef OOP_NEW_TILE_H
#define OOP_NEW_TILE_H

#include "../../Objects/Object.h"
#include "../../Landscape/ILandscape.h"
#include "../../Objects/Neutral/INeutral.h"

/*
 * Tile -- класс клетки игрового поля.
 * -----------------------------------------------
 * object -- объект, который находится на клетке игрового поля.
 * landscape -- тип ландшафта на клетке.
 * x, y -- координаты нахождения.
 */

class Tile
{
public:
    Tile() = default;
    ~Tile() = default;

    Object* object;
    INeutral* neutral;
    ILandscape* landscape;
    bool isBrightView;
    bool isDarkView;
    bool isUndeadView;
    int x, y;
};


#endif //OOP_NEW_TILE_H
