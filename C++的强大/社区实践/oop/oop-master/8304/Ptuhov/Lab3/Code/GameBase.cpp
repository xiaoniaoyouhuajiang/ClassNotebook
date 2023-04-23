#include "GameBase.h"

GameBase::GameBase()
{
	hp.increase(250);
}

size_t GameBase::getMaxUnitsCnt() const
{
	return units_cnt;
}

size_t GameBase::getNowUnitsCnt() const
{
	return units.size();
}

void GameBase::update(Point from, Point to)
{
	for (int i = 0; i < units.size(); ++i)
	{
		if (units[i] == from)
		{
			units[i] = to;
			return;
		}
	}
}

void GameBase::setUnitsCnt(size_t n)
{
	units_cnt = n;
}

void GameBase::addUnit(Point p)
{
	std::cout << "I add unit!\n";

	--units_cnt;
	units.push_back(p);
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
