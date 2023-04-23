#pragma once

#include <GAME/engine/Info.hpp>
#include <GAME/engine/Neutral.hpp>
#include <GAME/utils/Textures.hpp>
#include <GAME/engine/NeutralEffect.hpp>
#include <GAME/engine/Unit.hpp>

class ChancelEffect : public NeutralEffect {
public:
	ChancelEffect(istream& is, InObjectsTable& table) : NeutralEffect(is, table) {}
	ChancelEffect(int distance) : NeutralEffect(Effect::CHANCEL_EFFECT, Info::CHANCEL, distance) {}
	
	virtual float transformSpeed(float speed) const { return speed * 2; }
	virtual float transformAttack(float attack) const { return attack * 1.5; }
};

class Chancel : public Neutral {
public:
	Chancel(istream& is, InObjectsTable& table) : Neutral(is, table) {}

	Chancel() : Neutral() {
		texture(&Textures::getInstance().chancel());
		effectDistance(3);
	}

	virtual int info() const override {
		return Info::CHANCEL;
	}

	virtual void onUnitEntered(Unit& unit) override {
		unit.addEffect(new ChancelEffect(effectDistance()));
	}

	virtual void fillLogInfo(LogInfo& info) override {
		Neutral::fillLogInfo(info);
		info.name = "Chancel";
	}
};