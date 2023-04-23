#include "CarAttack.h"
#include "Unit.h"


CarAttack::CarAttack()
{
}



CarAttack::~CarAttack()
{
}

void CarAttack::attack(std::shared_ptr<Unit> unit) {
	std::vector<Point> points;
	Point point;
	point.x = unit->getX();
	point.y = unit->getY() - 1;
	points.push_back(point);

    unit->getMediator()->reactOnUnitAttack(unit->getWeapon()->getDamage() + unit->getLandDamage() + unit->getOwnDamage(), unit, points, true);
}
