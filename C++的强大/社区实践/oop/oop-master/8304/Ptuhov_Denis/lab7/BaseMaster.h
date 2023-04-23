#pragma once
#include "GameBase.h"

struct BaseMaster
{
	std::shared_ptr<GameBase> getBase();

private:
	std::shared_ptr<GameBase> base1;
};

