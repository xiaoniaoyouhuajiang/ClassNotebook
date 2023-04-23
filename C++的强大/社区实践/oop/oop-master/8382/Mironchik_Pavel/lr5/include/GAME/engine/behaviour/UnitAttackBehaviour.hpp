#pragma once

#include <SFML/System/Vector2.hpp>

#include <GAME/engine/AttachableProvider.hpp>

class Unit;

class UnitAttackBehaviour : public AttachableProvider<Unit> {
public:
	virtual bool attack(sf::Vector2i &cell) = 0;
	virtual bool attack(Unit& other) = 0;
};