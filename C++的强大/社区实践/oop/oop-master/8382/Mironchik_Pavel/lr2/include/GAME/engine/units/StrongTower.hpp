#pragma once

#include <GAME/engine/units/Tower.hpp>

class StrongTower: public Tower {
public:
	StrongTower(int squad): Tower(squad) {
		setAttackRange(5);
		setAttack(20);
		setMaxHealth(30);
		setTexture(Textures::getInstance().strongTower());
	}

	virtual int info() const override {
		return Info::STRONG_TOWER;
	}
};