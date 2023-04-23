#pragma once

#include <cmath>

#include <SFML/System/Vector2.hpp>

using std::abs;
using std::sqrt;
using std::pow;

class Utils {
public:
	static int computeDistance(const sf::Vector2i& a, const sf::Vector2i& b) {
		return abs(a.x - b.x) + abs(a.y - b.y);
	}

	static double computeMathDistance(const sf::Vector2i& a, const sf::Vector2i& b) {
		return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
	}
};