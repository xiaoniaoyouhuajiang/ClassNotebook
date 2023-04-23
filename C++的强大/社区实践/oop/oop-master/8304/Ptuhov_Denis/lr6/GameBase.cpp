#include "GameBase.h"


void GameBase::subscribe(std::shared_ptr<UnitBase> sub)
{
	units.push_back(sub);
}

void GameBase::unsubscribe(std::shared_ptr<UnitBase> sub)
{
	auto it = std::find(units.begin(), units.end(), sub);

	if (it == units.end())
		return;

	units.erase(it);
}

void GameBase::notify()
{
	for (auto& sub : units)
	{
		if (sub == nullptr)
			continue;

		sub->update();
	}
}

void GameBase::tellAboutSubscribers()
{
	std::cout << "\n";
	for (auto& sub : units)
	{
		if (sub == nullptr)
			continue;

		sub->tellAboutMe();
		std::cout << "\n";
	}
}
