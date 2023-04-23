#pragma once

#include <GAME/engine/Neutral.hpp>
#include <GAME/utils/Textures.hpp>
#include <GAME/engine/Info.hpp>
#include <GAME/engine/NeutralEffect.hpp>
#include <GAME/engine/Unit.hpp>

class BlackHoleEffect : public NeutralEffect {
public:
	BlackHoleEffect(istream& is, InObjectsTable& table) : NeutralEffect(is, table) {}
	BlackHoleEffect(int effectDistance)
		: NeutralEffect(Effect::BLACK_HOLE_EFFECT, Info::BLACK_HOLE, effectDistance) {};

	// TODO remove object on game tick
};

class BlackHole : public Neutral {
protected:

public:
	BlackHole(istream& is, InObjectsTable& table) : Neutral(is, table) {}

	BlackHole() : Neutral() {
		texture(&Textures::getInstance().blackHole());
		effectDistance(2);
	}

	virtual int info() const override {
		return Info::BLACK_HOLE;
	}

	virtual void onUnitEntered(Unit& unit) {
		unit.addEffect(new BlackHoleEffect(effectDistance()));
	}

	virtual void fillLogInfo(LogInfo& info) override {
		Neutral::fillLogInfo(info);
		info.name = "BlackHole";
	}
};