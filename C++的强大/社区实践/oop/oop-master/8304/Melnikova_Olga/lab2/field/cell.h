#pragma once
//#include "objects/object.h"
class Object;
class Landscape;

class Cell
{
public:
    Cell();
    Cell(int x, int y);
    ~Cell();
    Cell(const Cell &cell);
    Cell(Cell &&cell);
    Cell& operator=(const Cell &cell);
    Cell& operator=(const Cell &&cell);

    int x, y;
    Object *innerObject;
    Landscape* landscape;
};
