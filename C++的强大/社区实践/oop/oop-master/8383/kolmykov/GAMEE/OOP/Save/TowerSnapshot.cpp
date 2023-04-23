#include "TowerSnapshot.h"


TowerSnapshot::TowerSnapshot(int level, int hp, int damage, int size, int unitCount, Kind kind, std::shared_ptr<UnitFactory> factory, int x, int y)
:level(level), hp(hp), damage(damage), size(size), unitCount(unitCount), kind(kind), factory(factory), x(x), y(y){

}

TowerSnapshot::~TowerSnapshot()
{
}

int TowerSnapshot::getLevel()
{
	return level;
}

int TowerSnapshot::getHP()
{
	return hp;
}

int TowerSnapshot::getDamage()
{
	return damage;
}

int TowerSnapshot::getSize()
{
	return size;
}

int TowerSnapshot::getUnitCount()
{
	return unitCount;
}

std::shared_ptr<UnitFactory> TowerSnapshot::getFactory()
{
	return factory;
}


Kind TowerSnapshot::getKind() {
    return kind;
}


int TowerSnapshot::getX() {
    return x;
}


int TowerSnapshot::getY() {
    return y;
}
