#include "mediator.h"

#include "GameField/gamefield.h"


Mediator::Mediator(GameField* field)
{
    this->field = field;
}


bool Mediator::notify(Unit* unit, int x, int y)
{
    if (x < 0 || x >= field->getWidth() ||
            y < 0 || y >= field->getHeight()) {
        return false;
    }

    if (field->getCell(x, y)->isEmpty()) {
        field->getCell(unit->getCoordiante().x,
                       unit->getCoordiante().y)->deleteUnit();
        field->getCell(x, y)->addUnit(unit);

        return true;
    }

    return false;
}
