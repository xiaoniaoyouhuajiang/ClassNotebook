#include "GameBase.h"

GameBase::GameBase()
{
	hp.increase(250);
}

void GameBase::setUnitsCnt(size_t n)
{
	units_cnt = n;
}

void GameBase::createUnit(std::shared_ptr<UnitBase>& unit, Point p)
{
	if (units_cnt == 0)
		return;

	--units_cnt;
	units.push_back({ p, &unit });
}

void GameBase::forgetAbout(Point p)
{
	for (size_t i = 0; i < units.size(); ++i)
		if (units[i].p == p)
		{
			units.erase(units.begin() + i);
			++units_cnt;
			return;
		}

}
void GameBase::notify()
{
	for (auto& i : units)
		(*i.unit)->increaseDamage(20);
}
