#pragma once

#include <GAME/engine/units/Poor.hpp>

#include <GAME/utils/Textures.hpp>

class Peasant : public Poor {
public:
	Peasant(istream& is, InObjectsTable& table) : Poor(is, table) {}

	Peasant(int squad): Poor(squad) {
		setMaxHealth(10);
		setAttack(2);
		setTexture(Textures::getInstance().peasant());
	}

	virtual int info() const override {
		return Info::PEASANT;
	}

	virtual void fillLogInfo(LogInfo& info) override {
		Poor::fillLogInfo(info);
		info.name = "Peasant";
	}
};