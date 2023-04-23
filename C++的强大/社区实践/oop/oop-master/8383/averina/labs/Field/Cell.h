#ifndef OOP_CELL_H
#define OOP_CELL_H


//  Tile - класс клетки игрового поля.
//
//  object -- объект, который находится на клетке игрового поля.
//  x, y - координаты нахождения.


#include "Landscape/ILandscape.h"
#include "../Unit/NeutralObject/Object/INeutral.h"

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



#endif //OOP_CELL_H
