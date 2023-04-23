#include "CommonHumanMove.h"
#include "Unit.h"


CommonHumanMove::CommonHumanMove()
{
}


CommonHumanMove::~CommonHumanMove()
{
}

void CommonHumanMove::move(std::shared_ptr<Unit> unit) {
	unit->getMediator()->reactOnUnitMove(unit->getX(), unit->getY() - 1, unit);
}
