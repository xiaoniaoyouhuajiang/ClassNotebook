#pragma once

#include <GAME/engine/behaviour/UnitMoveBehaviour.hpp>
#include <GAME/utils/PathSearcher.hpp>
#include <GAME/utils/VectorsSet.hpp>

class BaseUnitMoveBehaviour : public UnitMoveBehaviour {
private:
	VectorsSet<int> _availableCells;
public:
	BaseUnitMoveBehaviour();
	BaseUnitMoveBehaviour(Provider<Unit>* provider);

	virtual void computeAvailableCells() override;
	virtual VectorsSet<int>& availableCells() override;

	virtual bool move(sf::Vector2i &toCell) override;
};