#include "SpitToAreaAttack.h"
#include "Unit.h"


SpitToAreaAttack::SpitToAreaAttack()
{
}


SpitToAreaAttack::~SpitToAreaAttack()
{
}

void SpitToAreaAttack::attack(std::shared_ptr<Unit> unit) {
	std::vector<Point> points;
	Point point1;
	point1.x = unit->getX();
	point1.y = unit->getY() + 1;
	points.push_back(point1);
	Point point2;
	point2.x = unit->getX();
	point2.y = unit->getY() + 2;
	points.push_back(point2);
	Point point3;
	point3.x = unit->getX() - 1;
	point3.y = unit->getY() + 1;
	points.push_back(point3);
	Point point4;
	point4.x = unit->getX() + 1;
	point4.y = unit->getY() + 1;
	points.push_back(point4);

    unit->getMediator()->reactOnUnitAttack(unit->getWeapon()->getDamage() + unit->getLandDamage() + unit->getOwnDamage(), unit, points, true);
}
