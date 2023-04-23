#pragma once

#include <GAME/engine/Unit.hpp>

class Tower : public Unit {
public:
	Tower(istream& is, InObjectsTable& table) : Unit(is, table) {}

	Tower(int squad): Unit(squad) {
		setSpeed(0);
		setMaxHealth(50);
	}

	virtual void fillLogInfo(LogInfo& info) override {
		Unit::fillLogInfo(info);
		info.name = "Tower";
	}
};