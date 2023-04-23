#include <GAME/utils/Textures.hpp>

Textures* Textures::instance = nullptr;

Textures::Textures() {
	_peasant.loadFromFile("assets\\images\\peasant.png");
	_bum.loadFromFile("assets\\images\\bum.png");
	_mounted_warrior.loadFromFile("assets\\images\\mounted_warrior.png");
	_mounted_shooter.loadFromFile("assets\\images\\mounted_shooter.png");
	_clever_tower.loadFromFile("assets\\images\\clever_tower.png");
	_strong_tower.loadFromFile("assets\\images\\strong_tower.png");
	_home.loadFromFile("assets\\images\\home.png");
	_sea.loadFromFile("assets\\images\\terrain\\sea.jpg");
	_lava.loadFromFile("assets\\images\\terrain\\lava.jpg");
	_ground.loadFromFile("assets\\images\\terrain\\ground.jpg");
	_stone.loadFromFile("assets\\images\\stone.png");
	_heal.loadFromFile("assets\\images\\heal.png");
	_chancel.loadFromFile("assets\\images\\chancel.png");
	_blackHole.loadFromFile("assets\\images\\black_hole.png");
}

Textures& Textures::getInstance() {
	if (instance == nullptr)
		instance = new Textures();

	return *instance;
}

sf::Texture& Textures::peasant() {
	return _peasant;
}

sf::Texture& Textures::bum() {
	return _bum;
}

sf::Texture& Textures::mountedWarrior() {
	return _mounted_warrior;
}

sf::Texture& Textures::mountedShooter() {
	return _mounted_shooter;
}

sf::Texture& Textures::cleverTower() {
	return _clever_tower;
}

sf::Texture& Textures::strongTower() {
	return _strong_tower;
}

sf::Texture& Textures::home() {
	return _home;
}

sf::Texture& Textures::stone() {
	return _stone;
}

sf::Texture& Textures::heal() {
	return _heal;
}

sf::Texture& Textures::chancel() {
	return _chancel;
}

sf::Texture& Textures::blackHole() {
	return _blackHole;
}

sf::Texture& Textures::sea() {
	return _sea;
}

sf::Texture& Textures::lava() {
	return _lava;
}

sf::Texture& Textures::ground() {
	return _ground;
}