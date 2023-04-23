#include "cellofgamefield.h"


CellOfGameField::CellOfGameField()
{
    this->empty = true;
    unit = nullptr;
}


CellOfGameField::CellOfGameField(const CellOfGameField& cell)
{
    this->empty = cell.empty;
    this->unit = unit->clone();
}


CellOfGameField& CellOfGameField::operator=(CellOfGameField& cell)
{
    if (this == &cell) {
        return *this;
    }

    this->empty = cell.empty;

    if (!cell.empty) {
        this->unit = cell.unit->clone();
    }

    return *this;
}


bool CellOfGameField::isEmpty()
{
    return this->empty;
}


void CellOfGameField::addUnit(Unit* unit)
{
    this->unit = unit;
    this->empty = false;
}


void CellOfGameField::deleteUnit()
{
    this->unit = nullptr;
    this->empty = true;
}


Unit* CellOfGameField::getUnit()
{
    return this->unit;
}
