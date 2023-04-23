#include <GAME/utils/Textures.hpp>
#include <cassert>

Textures* Textures::instance = nullptr;

const int Textures::PEASANT = 0;
const int Textures::BUM = 1;
const int Textures::MOUNTED_WARRIOR = 2;
const int Textures::MOUNTED_SHOOTER = 3;
const int Textures::CLEVER_TOWER = 4;
const int Textures::STRONG_TOWER = 5;
const int Textures::HOME = 6;
const int Textures::STONE = 7;
const int Textures::HEAL = 8;
const int Textures::CHANCEL = 9;
const int Textures::BLACK_HOLE = 10;
const int Textures::SEA = 11;
const int Textures::LAVA = 12;
const int Textures::GROUND = 13;

sf::Texture* Textures::readTexture(istream& is, InObjectsTable& table) {
	int t;
	Serializer::readInt(is, &t);

	switch (t) {
		case PEASANT:			return &Textures::instance->_peasant;
		case BUM:				return &Textures::instance->_bum;
		case MOUNTED_WARRIOR:	return &Textures::instance->_mounted_warrior;
		case MOUNTED_SHOOTER:	return &Textures::instance->_mounted_shooter;
		case CLEVER_TOWER:		return &Textures::instance->_clever_tower;
		case STRONG_TOWER:		return &Textures::instance->_strong_tower;
		case HOME:				return &Textures::instance->_home;
		case STONE:				return &Textures::instance->_stone;
		case HEAL:				return &Textures::instance->_heal;
		case CHANCEL:			return &Textures::instance->_chancel;
		case BLACK_HOLE:		return &Textures::instance->_blackHole;
		case SEA:				return &Textures::instance->_sea;
		case LAVA:				return &Textures::instance->_lava;
		case GROUND:			return &Textures::instance->_ground;
		default:				return nullptr;
	}
}

void Textures::writeTexture(ostream& os, OutObjectsTable& table, const sf::Texture* texture) {
	int t = -1;

	if (texture == &Textures::instance->_peasant)			t = PEASANT;
	if (texture == &Textures::instance->_bum)				t = BUM;
	if (texture == &Textures::instance->_mounted_warrior)	t = MOUNTED_WARRIOR;
	if (texture == &Textures::instance->_mounted_shooter)	t = MOUNTED_SHOOTER;
	if (texture == &Textures::instance->_clever_tower)		t = CLEVER_TOWER;
	if (texture == &Textures::instance->_strong_tower)		t = STRONG_TOWER;
	if (texture == &Textures::instance->_home)				t = HOME;
	if (texture == &Textures::instance->_stone)				t = STONE;
	if (texture == &Textures::instance->_heal)				t = HEAL;
	if (texture == &Textures::instance->_chancel)			t = CHANCEL;
	if (texture == &Textures::instance->_blackHole)			t = BLACK_HOLE;
	if (texture == &Textures::instance->_sea)				t = SEA;
	if (texture == &Textures::instance->_lava)				t = LAVA;
	if (texture == &Textures::instance->_ground)			t = GROUND;

	Serializer::writeInt(os, &t);
}

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