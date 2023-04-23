#pragma once

#include <SFML/System/Vector2.hpp>
#include <GAME/engine/AttachableProvider.hpp>

template<class T>
class CellClickBehaviour : public AttachableProvider<T> {
public:
	virtual bool onCellClick(sf::Vector2i &cell) = 0;
};