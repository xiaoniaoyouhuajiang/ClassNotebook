#pragma once

#include <GAME/engine/units/Mounted.hpp>

class MountedWarrior : public Mounted {
public:
	MountedWarrior(int squad): Mounted(squad) {
		setAttackRange(2);
		setAttack(7);
		setMaxHealth(30);
		setTexture(Textures::getInstance().mountedWarrior());
	}

	virtual int info() const override {
		return Info::MOUNTED_WARRIOR;
	}
};