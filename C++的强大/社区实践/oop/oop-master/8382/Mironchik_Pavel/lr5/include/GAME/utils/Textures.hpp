#pragma once

#include <iostream>

#include <SFML/Graphics/Texture.hpp>
#include <GAME/serialize/Serializer.hpp>
#include <GAME/serialize/InObjectsTable.hpp>
#include <GAME/serialize/OutObjectsTable.hpp>

using std::istream;
using std::ostream;

class Textures {
private:
	static const int PEASANT;
	static const int BUM;
	static const int MOUNTED_WARRIOR;
	static const int MOUNTED_SHOOTER;
	static const int CLEVER_TOWER;
	static const int STRONG_TOWER;
	static const int HOME;
	static const int STONE;
	static const int HEAL;
	static const int CHANCEL;
	static const int BLACK_HOLE;
	static const int SEA;
	static const int LAVA;
	static const int GROUND;

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
	static void writeTexture(ostream& os, OutObjectsTable& table, const sf::Texture* texture);
	static sf::Texture* readTexture(istream& is, InObjectsTable& table);

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