#pragma once

#include <GAME/engine/units/Poor.hpp>
#include <GAME/utils/Textures.hpp>
#include <GAME/engine/Info.hpp>

class BumSoldier : public Poor {
public:
	BumSoldier(int squad): Poor(squad) {
		setMaxHealth(5);
		setAttack(4);
		setSpeed(2);
		setTexture(Textures::getInstance().bum());
	}

	BumSoldier(BumSoldier& from) : Poor(from) {}

	virtual int info() const override {
		return Info::BUM_SOLDIER;
	}

	GameObject* copy() override {
		return new BumSoldier(*this);
	}
};