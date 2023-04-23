#pragma once

#include <cmath>

#include <SFML/System/Vector2.hpp>

#include <GAME/engine/GameBoard.hpp>
#include <GAME/engine/Terrain.hpp>

class MapConstructor {
public:
	template<typename T>
	static void circle(GameBoard* board, sf::Vector2i center, int radius) {
		for (int x = 0; x < board->getCellsCount().x; x++)
			for (int y = 0; y < board->getCellsCount().y; y++) {
				if (std::sqrt((double) ((x - center.x)*(x - center.x) + (y - center.y)*(y - center.y))) <= radius) {
					board->getCell(sf::Vector2i(x, y)).terrain(shared_ptr<Terrain>(new T()));
				}
			}
	}
};