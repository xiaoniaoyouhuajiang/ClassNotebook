#pragma once

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Color.hpp>

class BoardView;
class Unit;

class HealthDrawer: public sf::Drawable{
private:
	const Unit* _unit;
	const sf::Color _paleColor = sf::Color(255, 0, 0, 255);
	const sf::Color _lightColor = sf::Color(0, 255, 0, 255);
	
public:
	HealthDrawer(const Unit& unit);

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};