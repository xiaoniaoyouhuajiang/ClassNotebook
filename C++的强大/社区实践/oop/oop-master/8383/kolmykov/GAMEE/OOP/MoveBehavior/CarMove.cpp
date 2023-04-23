#include "CarMove.h"
#include "Unit.h"


CarMove::CarMove()
{
}


CarMove::~CarMove()
{
}

void CarMove::move(std::shared_ptr<Unit> unit)
{
	unit->getMediator()->reactOnUnitMove(unit->getX(), unit->getY() - 2, unit);
}
