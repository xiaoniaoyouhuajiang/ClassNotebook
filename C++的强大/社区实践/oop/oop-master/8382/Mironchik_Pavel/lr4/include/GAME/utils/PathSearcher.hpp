#pragma once

#include <SFML/System/Vector2.hpp>

#include <GAME/utils/List.hpp>
#include <functional>

enum PathPointLocation {
	NONE,
	LEFT,
	TOP,
	RIGHT,
	BOTTOM
};

struct PathPoint {
	PathPoint* left = nullptr,
		*top = nullptr,
		*right = nullptr,
		*bottom = nullptr;
	sf::Vector2i coords;
	int pathLength = 0;
	PathPoint* from = nullptr;

	PathPoint(sf::Vector2i& coords) : coords(coords) {};
};

class PathSearcher {
private:
	List<PathPoint*>* points = nullptr;

	void addPoint(PathPoint* from, PathPointLocation location);
public:
	~PathSearcher();

	void computePaths(sf::Vector2i start, std::function<bool(sf::Vector2i&)> canGo, int maxPathLength);

	List<PathPoint*>* getPaths() const;

	void clear();
};