#pragma once

#include <GAME/engine/units/Mounted.hpp>

class MountedShooter : public Mounted {
public:
	MountedShooter(istream& is, InObjectsTable& table) : Mounted(is, table) {}

	MountedShooter(int squad): Mounted(squad) {
		setAttackRange(5);
		setAttack(5);
		setMaxHealth(25);
		setTexture(Textures::getInstance().mountedShooter());
	}
	
	virtual int info() const override {
		return Info::MOUNTED_SHOOTER;
	}

	virtual void fillLogInfo(LogInfo& info) override {
		Mounted::fillLogInfo(info);
		info.name = "MountedShooter";
	}
};