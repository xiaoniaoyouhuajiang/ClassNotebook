#include "pch.h"
#include "GameUtilities.h"


GameUtilities::GameUtilities() {
}


GameUtilities::~GameUtilities() {
}

void GameUtilities::clamp(int &value, int max, int min) {
	if (value > max) value = max;
	if (value < min) value = min;
}

void GameUtilities::clamp(Vector2D &value, int max, int min) {
	if (value.x > max) value.x = max;
	if (value.x < min) value.x = min;

	if (value.y > max) value.y = max;
	if (value.y < min) value.y = min;
}

void GameUtilities::clamp(Vector2D &value, Vector2D max, Vector2D min) {
	if (value.x > max.x) value.x = max.x;
	if (value.x < min.x) value.x = min.x;

	if (value.y > max.y) value.y = max.y;
	if (value.y < min.y) value.y = min.y;
}
