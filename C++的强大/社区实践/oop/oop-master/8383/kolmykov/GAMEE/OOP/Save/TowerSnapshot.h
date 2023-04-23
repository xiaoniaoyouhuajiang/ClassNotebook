#pragma once
#include <memory>
#include "UnitFactory.h"


class TowerSnapshot
{
private:
	int level;
	int hp;
	int damage;
	int size;
	int unitCount;
    Kind kind;
	std::shared_ptr<UnitFactory> factory;
    int x;
    int y;
public:
    TowerSnapshot(int level, int hp, int damage, int size, int unitCount, Kind kind, std::shared_ptr<UnitFactory> factory, int x, int y);
	~TowerSnapshot();
	int getLevel();
	int getHP();
	int getDamage();
	int getSize();
	int getUnitCount();
    Kind getKind();
	std::shared_ptr<UnitFactory> getFactory();
    int getX();
    int getY();
};

