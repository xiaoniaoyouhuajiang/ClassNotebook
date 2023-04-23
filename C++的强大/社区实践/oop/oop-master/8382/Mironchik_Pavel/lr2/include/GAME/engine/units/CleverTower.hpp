#pragma once

#include <GAME/engine/units/Tower.hpp>
#include <GAME/utils/Textures.hpp>
#include <GAME/engine/Info.hpp>

class CleverTower : public Tower {
public:
	CleverTower(int squad) : Tower(squad) {
		setAttackRange(2);
		setAttack(7);
		setMaxHealth(30);
		setTexture(Textures::getInstance().cleverTower());
	}

	virtual int info() const override {
		return Info::CLEVER_TOWER;
	}
};