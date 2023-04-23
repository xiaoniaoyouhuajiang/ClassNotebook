#pragma once

#include <SFML/System/Vector2.hpp>
#include <GAME/engine/AttachableProvider.hpp>
#include <GAME/utils/VectorsSet.hpp>

class Unit;

class UnitMoveBehaviour : public AttachableProvider<Unit> {
public:
	virtual void computeAvailableCells() = 0;
	virtual VectorsSet<int>& availableCells() = 0;
	virtual bool move(sf::Vector2i &toCell) = 0;
};