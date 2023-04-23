#include "BikeMove.h"
#include "Unit.h"


BikeMove::BikeMove()
{
}


BikeMove::~BikeMove()
{
}

void BikeMove::move(std::shared_ptr<Unit> unit)
{
	unit->getMediator()->reactOnUnitMove(unit->getX(), unit->getY() - 3, unit);
}
