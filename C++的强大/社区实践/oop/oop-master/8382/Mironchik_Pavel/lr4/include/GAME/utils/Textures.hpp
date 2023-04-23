#pragma once

#include <SFML/Graphics/Texture.hpp>

class Textures {
private:
	sf::Texture _peasant;
	sf::Texture _bum;
	sf::Texture _mounted_warrior;
	sf::Texture _mounted_shooter;
	sf::Texture _clever_tower;
	sf::Texture _strong_tower;
	sf::Texture _home;

	sf::Texture _stone;
	sf::Texture _heal;
	sf::Texture _chancel;
	sf::Texture _blackHole;

	sf::Texture _sea;
	sf::Texture _lava;
	sf::Texture _ground;
	
private:
	static Textures *instance;
	Textures();

public:
	static Textures& getInstance();

	sf::Texture& peasant();
	sf::Texture& bum();
	sf::Texture& mountedWarrior();
	sf::Texture& mountedShooter();
	sf::Texture& cleverTower();
	sf::Texture& strongTower();
	sf::Texture& home();

	sf::Texture& stone();
	sf::Texture& heal();
	sf::Texture& chancel();
	sf::Texture& blackHole();

	sf::Texture& sea();
	sf::Texture& lava();
	sf::Texture& ground();

};