#ifndef CELLOFGAMEFIELD_H
#define CELLOFGAMEFIELD_H

#include "Unit/unit.h"


class CellOfGameField
{
public:
    CellOfGameField();
    ~CellOfGameField() = default;

    CellOfGameField(const CellOfGameField& cell);
    CellOfGameField& operator=(CellOfGameField& cell);

    bool isEmpty();
    void addUnit(Unit* unit);
    void deleteUnit();
    Unit* getUnit();

protected:
    Unit* unit;
    bool empty;
};

#endif // CELLOFGAMEFIELD_H
