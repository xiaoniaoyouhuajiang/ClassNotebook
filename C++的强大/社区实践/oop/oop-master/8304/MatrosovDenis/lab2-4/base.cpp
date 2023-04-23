#include "base.h"

Base::Base(int x, int y, Factions f, std::shared_ptr<GameMap> Map)
{
	X_CORD = x;
	Y_CORD = y;
	ObjectFactions = f;
	LNK_TO_MAP = Map;
	CountOfUnit = 0;
	MaxCountOfUnit = 20;
	LVL1 = ArmyFirstGradeLevel();
	LVL2 = ArmySecondGradeLevel();
	MaxHP = 1000;
	HP = MaxHP;
	if (f == Factions::Player)
		Map->setUserBase(*this);
	else if (f == Factions::Enemy)
		Map->setEnemyBase(*this);
}

Base::~Base()
{

}

bool Base::createUnit(int x, int y, size_t unitType)
{
	bool flag = false;
	BaseUnit newUnit;
	if (MaxCountOfUnit > CountOfUnit) {
		switch (unitType)
		{
		case 1:
			newUnit = LVL1.createMelleUnit(x, y, ObjectFactions);
			break;
		case 2:
			newUnit = LVL2.createMelleUnit(x, y, ObjectFactions);
			break;
		case 3:
			newUnit = LVL1.createMountUnit(x, y, ObjectFactions);
			break;
		case 4:
			newUnit = LVL2.createMountUnit(x, y, ObjectFactions);
			break;
		case 5:
			newUnit = LVL1.createLongaRangeUnit(x, y, ObjectFactions);
			break;
		case 6:
			newUnit = LVL2.createLongaRangeUnit(x, y, ObjectFactions);
			break;
		default:
			//ERROR
			break;
		}

		flag = LNK_TO_MAP->addObject(newUnit);
		if (flag) {
			units.Push(newUnit);
			CountOfUnit++;
		}
	}
	return flag;
}

void Base::checkUnits() {
	Node tmp_head = units.takeHead();
	std::vector<Node> toDeath;

	while (tmp_head.data!=nullptr) {
		if (tmp_head.data->HP() <= 0) {
			toDeath.push_back(tmp_head);
		}
		tmp_head = *tmp_head.next;
	}

	for (auto i : toDeath) {
		LNK_TO_MAP->removeObject(*i.data);
		units.Remove(i.data->getX(), i.data->getY());
	}	
}