#pragma once

#include <GAME/engine/units/Mounted.hpp>

class MountedShooter : public Mounted {
public:
	MountedShooter(int squad): Mounted(squad) {
		setAttackRange(5);
		setAttack(5);
		setMaxHealth(25);
		setTexture(Textures::getInstance().mountedShooter());
	}
	
	virtual int info() const override {
		return Info::MOUNTED_SHOOTER;
	}
};