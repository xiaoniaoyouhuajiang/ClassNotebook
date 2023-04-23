#include "SwordAttack.h"
#include "Unit.h"


SwordAttack::SwordAttack() {

}


SwordAttack::~SwordAttack() {

}

void SwordAttack::attack(std::shared_ptr<Unit> unit) {
	std::vector<Point> points;
	Point point1;
	point1.x = unit->getX();
	point1.y = unit->getY() - 1;
	points.push_back(point1);

    unit->getMediator()->reactOnUnitAttack(unit->getWeapon()->getDamage() + unit->getLandDamage() + unit->getOwnDamage(), unit, points, true);
}
