#pragma once

#include <set>

#include <SFML/System/Vector2.hpp>

using std::set;

template<class T>
class VectorsComparator {
public:
	bool operator()(const sf::Vector2<T>& ef1, const sf::Vector2<T>& ef2) const {
		return ef1.x < ef2.x || (ef1.x == ef2.x && ef1.y < ef2.y);
	}
};

template<class T>
class VectorsSet : public set<sf::Vector2<T>, VectorsComparator<T>> {
};
