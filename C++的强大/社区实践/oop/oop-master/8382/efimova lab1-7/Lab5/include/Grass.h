#pragma once
#include "TerrainBoardUnit.h"
class Grass : public TerrainBoardUnit
{
public:
	Grass() {};
	std::vector<ActionMeta> turnAction() override;
	bool isPassable() override;
	std::string getName() override;
	//TerrainType getTerrainType() override;
};

