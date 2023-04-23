#pragma once
#include "GameObjects.h"
#include "GameMap.h"
#include <vector>
/*
######################################################
Класс базы
######################################################
*/

class Base : public MapStructure
{
public:
	Base(int x, int y, Factions f, std::shared_ptr<GameMap> Map);
	~Base();

	bool createUnit(int x, int y, size_t unitType);

	void checkUnits();

	size_t Alive() {
		return HP > 0;
	}
	void getDamage(int damage) {
		HP -= damage;
	}
private:
	ArmyFirstGradeLevel LVL1;
	ArmySecondGradeLevel LVL2;

	std::shared_ptr<GameMap> LNK_TO_MAP;

	size_t HP;
	size_t MaxHP;
	size_t CountOfUnit;
	size_t MaxCountOfUnit;
	MyList units;
};

