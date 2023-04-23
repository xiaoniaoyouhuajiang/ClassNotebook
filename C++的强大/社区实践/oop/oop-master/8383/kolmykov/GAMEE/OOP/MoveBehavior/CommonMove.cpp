#include "CommonMove.h"
#include "Unit.h"


CommonMove::CommonMove()
{
}


CommonMove::~CommonMove()
{
}

void CommonMove::move(std::shared_ptr<Unit> unit) {
	unit->getMediator()->reactOnUnitMove(unit->getX(), unit->getY() + 1, unit);
}

