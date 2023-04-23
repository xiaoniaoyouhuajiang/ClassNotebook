#include "FieldCell.hpp"


FieldCell::FieldCell()
{
    empty = true;
}


FieldCell::FieldCell(const FieldCell& cell)
{

    if (cell.unit) {
        this->unit = cell.unit->clone();
    }

    this->empty = cell.empty;
}


FieldCell::FieldCell(FieldCell&& cell)
{
    this->unit = std::move(cell.unit);
    this->empty = cell.empty;

    cell.empty = true;
}


FieldCell& FieldCell::operator=(const FieldCell& cell)
{
    if (this == &cell) {
        return *this;
    }

    this->unit.reset();
    if (!cell.isEmpty()) {
        this->unit = cell.unit->clone();
    }

    this->empty = cell.empty;

    return *this;
}


FieldCell& FieldCell::operator=(FieldCell&& cell)
{
    if (this == &cell) {
        return *this;
    }

    this->unit.reset();

    this->unit = std::move(cell.unit);
    this->empty = false;

    cell.empty = true;

    return *this;
}


void FieldCell::addUnit(std::shared_ptr<Unit> unit)
{
    this->unit = unit;
    this->empty = false;
}


void FieldCell::deleteUnit()
{
    this->unit = nullptr;

    this->empty = true;
}


std::shared_ptr<Unit> FieldCell::getUnit()
{
    return unit;
}

bool FieldCell::isEmpty() const
{
    return empty;
}

