#include "StinkyAttack.h"
#include "Unit.h"


StinkyAttack::StinkyAttack() {

}


StinkyAttack::~StinkyAttack() {

}

void StinkyAttack::attack(std::shared_ptr<Unit> unit) {
	std::vector<Point> points;
	Point point1;
	point1.x = unit->getX();
	point1.y = unit->getY() + 1;
	Point point2;
	point2.x = unit->getX() + 1;
	point2.y = unit->getY();
	Point point3;
	point3.x = unit->getX() - 1;
	point3.y = unit->getY();
	points.push_back(point1);
	points.push_back(point2);
	points.push_back(point3);

    unit->getMediator()->reactOnUnitAttack(unit->getWeapon()->getDamage() + unit->getOwnDamage() + unit->getLandDamage(), unit, points, false);
}
