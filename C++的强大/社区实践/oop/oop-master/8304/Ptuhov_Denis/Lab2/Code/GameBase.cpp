#include "GameBase.h"

GameBase::GameBase()
{
	hp.increase(250);
}

void GameBase::setUnitsCnt(size_t n)
{
	units_cnt = n;
}

bool GameBase::addUnit(Point p)
{
	if (units_cnt == 0)
		return false;

	std::cout << "I add unit!\n";

	--units_cnt;
	units.push_back(p);
	return true;
}

void GameBase::forgetAbout(Point p)
{
	for (size_t i = 0; i < units.size(); ++i)
		if (units[i] == p)
		{
			units.erase(units.begin() + i);
			++units_cnt;
			std::cout << "I delete unit!\n";
			return;
		}

}
std::vector<Point> GameBase::notify()
{
	return units;
}
