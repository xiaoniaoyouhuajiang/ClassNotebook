#pragma once
#include <memory>
#include <vector>
#include "UnitBase.h"

struct GameBase
{
	void subscribe(std::shared_ptr<UnitBase> sub);
	void unsubscribe(std::shared_ptr<UnitBase> sub);
	void notify();

	void tellAboutSubscribers();

private:
	std::vector<std::shared_ptr<UnitBase>> units;
};