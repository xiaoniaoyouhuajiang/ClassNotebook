#ifndef OOP1_CELL_H
#define OOP1_CELL_H

#include "Unit.h"
#include "Landscape.h"
#include "Base.h"
#include "NeutralObject.h"

struct Cell{
    int x, y;
    Unit* unit;
    Landscape* landscape;
    Base* base;
    NeutralObject* neutralObject;
};

#endif //OOP1_CELL_H
