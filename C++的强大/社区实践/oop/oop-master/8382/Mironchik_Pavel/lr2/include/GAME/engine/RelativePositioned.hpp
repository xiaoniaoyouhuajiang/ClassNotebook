#pragma once

#include <GAME/utils/FixedArray.hpp>
#include <SFML/System/Vector2.hpp>

class RelativePositioned {
private:
	sf::Vector2f relativePosition;

public:
	void setRelativeX(float cellX);

	void setRelativeY(float cellY);

	float getRelativeX();

	float getRelativeY();

	void setRelativePosition(sf::Vector2f& position);

	sf::Vector2f& getRelativePosition();

	void offsetRelativeX(float dx);

	void offsetRelativeY(float dy);
};