#pragma once

class Unit;
class ITerrain {

public:
	virtual void doTerrainEffect(Unit*& target) = 0;

	virtual ~ITerrain() = default;
};

