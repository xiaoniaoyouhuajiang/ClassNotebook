#include "FatZombyMoveBehavior.h"
#include "Unit.h"


FatZombyMoveBehavior::FatZombyMoveBehavior()
{
	step = 0;
}


FatZombyMoveBehavior::~FatZombyMoveBehavior() {

}

void FatZombyMoveBehavior::move(std::shared_ptr<Unit> unit)
{
	if (step == 0) {
		unit->getMediator()->reactOnUnitMove(unit->getX(), unit->getY() + 1, unit);
	}
	step = (step + 1) % 2;
}
