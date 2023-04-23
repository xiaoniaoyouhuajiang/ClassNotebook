#pragma once
#include "TerrainBoardUnit.h"
class River : public TerrainBoardUnit
{
public:
	River() {};
	std::vector<ActionMeta> turnAction() override;
	bool isPassable() override;
	std::string getName() override;
};

