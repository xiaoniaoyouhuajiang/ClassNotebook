#pragma once

#include <GAME/engine/Unit.hpp>

#include <GAME/utils/Textures.hpp>

class Poor : public Unit {
public:
	Poor(istream& is, InObjectsTable& table) : Unit(is, table) {}

	Poor(int squad): Unit(squad) {
		setSpeed(3);
		setAttackRange(1);
	}

	Poor(Poor& from) : Unit(from) {}

	virtual void fillLogInfo(LogInfo& info) override {
		Unit::fillLogInfo(info);
		info.name = "Poor";
	}
};