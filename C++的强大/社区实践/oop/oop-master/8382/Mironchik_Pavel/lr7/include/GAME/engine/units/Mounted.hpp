#pragma once

#include <GAME/engine/Unit.hpp>

#include <GAME/utils/Textures.hpp>

class Mounted : public Unit {
public:
	Mounted(istream& is, InObjectsTable& table) : Unit(is, table) {}

	Mounted(int squad): Unit(squad) {
		setSpeed(5);
	}

	virtual void fillLogInfo(LogInfo& info) override {
		Unit::fillLogInfo(info);
		info.name = "Mounted";
	}
};