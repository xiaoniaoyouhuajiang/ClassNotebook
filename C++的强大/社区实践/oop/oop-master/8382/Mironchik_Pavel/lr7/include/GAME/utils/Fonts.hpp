#pragma once

#include <SFML/Graphics/Font.hpp>

class Fonts {
private:
	static Fonts* _instance;
	sf::Font _main;

	Fonts();

public:
	static Fonts& instance();

	sf::Font& main();
};