#include <GAME/utils/PathSearcher.hpp>

PathSearcher::~PathSearcher() {
	clear();
}

void PathSearcher::computePaths(sf::Vector2i start, std::function<bool(sf::Vector2i&)> canGo, int maxPathLength) {
	clear();
	points = new List<PathPoint*>();
	PathPoint* startPoint = new PathPoint(start);
	points->add(startPoint);

	for (PathPoint* point : *points) {
		if (point->pathLength >= maxPathLength)
			continue;

		sf::Vector2i pos = point->coords;
		
		pos.x = point->coords.x + 1;
		if (point->right == nullptr && canGo(pos)) {
			addPoint(point, RIGHT);
		}
		pos.x = point->coords.x - 1;
		if (point->left == nullptr && canGo(pos)) {
			addPoint(point, LEFT);
		}
		pos.x = point->coords.x;
		pos.y = point->coords.y - 1;
		if (point->top == nullptr && canGo(pos)) {
			addPoint(point, TOP);
		}
		pos.y = point->coords.y + 1;
		if (point->bottom == nullptr && canGo(pos)) {
			addPoint(point, BOTTOM);
		}
	}
}

void PathSearcher::addPoint(PathPoint* from, PathPointLocation location) {
	sf::Vector2i newCoords = from->coords;

	if (location == LEFT)
		newCoords.x -= 1;
	if (location == TOP)
		newCoords.y -= 1;
	if (location == RIGHT)
		newCoords.x += 1;
	if (location == BOTTOM)
		newCoords.y += 1;

	for (PathPoint* point : *points) {
		if (point->coords == newCoords)
			return;
	}

	PathPoint* point = new PathPoint(newCoords);
	point->pathLength = from->pathLength + 1;
	point->from = from;
	
	if (location == LEFT) {
		point->right = from;
		from->left = point;
	}
	if (location == TOP) {
		point->bottom = from;
		from->top = point;
	}
	if (location == RIGHT) {
		point->left = from;
		from->right = point;
	}
	if (location == BOTTOM) {
		point->top = from;
		from->bottom = point;
	}

	points->add(point);
}

List<PathPoint*>* PathSearcher::getPaths() const {
	return points;
}

void PathSearcher::clear() {
	if (points == nullptr)
		return;

	for (PathPoint* point : *points)
		delete point;

	delete points;
	points = nullptr;
}