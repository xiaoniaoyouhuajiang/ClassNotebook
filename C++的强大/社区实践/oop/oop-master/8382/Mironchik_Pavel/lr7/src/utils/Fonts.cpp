#include <GAME/utils/Fonts.hpp>

Fonts* Fonts::_instance = nullptr;


Fonts& Fonts::instance() {
	if (_instance == nullptr)
		_instance = new Fonts();

	return *_instance;
}

Fonts::Fonts() {
	_main.loadFromFile("D:\\University\\3_course\\OOP\\Game\\SimpleGame\\Debug\\assets\\fonts\\arial.ttf");
}

sf::Font& Fonts::main() {
	return _main;
}