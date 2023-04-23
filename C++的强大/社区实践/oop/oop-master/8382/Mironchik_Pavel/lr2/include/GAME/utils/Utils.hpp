#pragma once

#include <cmath>

#include <SFML/System/Vector2.hpp>

class Utils {
public:
	static int computeDistance(const sf::Vector2i& a, const sf::Vector2i& b) {
		return std::abs(a.x - b.x) + std::abs(a.y - b.y);
	}
};