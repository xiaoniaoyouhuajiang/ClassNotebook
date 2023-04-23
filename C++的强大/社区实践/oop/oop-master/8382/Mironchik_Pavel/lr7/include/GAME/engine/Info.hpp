#pragma once

#include <map>

#include <SFML/Graphics/Texture.hpp>

#include <GAME/utils/Textures.hpp>

using std::map;

class Info {
private:
	static Info* _instance;
	map<int, sf::Texture*> _idToTexture;

	Info() {
		_idToTexture.clear();
		_idToTexture[BUM_SOLDIER] = &Textures::getInstance().bum();
		_idToTexture[CLEVER_TOWER] = &Textures::getInstance().cleverTower();
		_idToTexture[MOUNTED_SHOOTER] = &Textures::getInstance().mountedShooter();
		_idToTexture[MOUNTED_WARRIOR] = &Textures::getInstance().mountedWarrior();
		_idToTexture[PEASANT] = &Textures::getInstance().peasant();
		_idToTexture[STRONG_TOWER] = &Textures::getInstance().strongTower();
		_idToTexture[HOME] = &Textures::getInstance().home();
		_idToTexture[STONE] = &Textures::getInstance().stone();
		_idToTexture[HEAL] = &Textures::getInstance().heal();
		_idToTexture[CHANCEL] = &Textures::getInstance().chancel();
	}

public:
	static const int UNKNOWN = -1;

	static const int BUM_SOLDIER = 1;
	static const int CLEVER_TOWER = 2;
	static const int MOUNTED_SHOOTER = 3;
	static const int MOUNTED_WARRIOR = 4;
	static const int PEASANT = 5;
	static const int STRONG_TOWER = 6;

	static const int HOME = 51;
	static const int HEAL = 52;
	static const int CHANCEL = 53;
	static const int BLACK_HOLE = 54;

	static const int STONE = 101;

	static Info& instance() {
		if (_instance == nullptr)
			_instance = new Info();
		return *_instance;
	}

	sf::Texture* getTextureByInfo(int info) {
		if (!_idToTexture.count(info))
			return nullptr;

		return _idToTexture[info];
	}
};