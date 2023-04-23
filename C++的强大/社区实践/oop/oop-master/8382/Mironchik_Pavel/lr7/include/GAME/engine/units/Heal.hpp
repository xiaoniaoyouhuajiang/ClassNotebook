#pragma once

#include <GAME/engine/Info.hpp>
#include <GAME/engine/Neutral.hpp>
#include <GAME/utils/Textures.hpp>
#include <GAME/engine/NeutralEffect.hpp>
#include <GAME/engine/Unit.hpp>

class HealEffect : public NeutralEffect {
public:
	HealEffect(istream& is, InObjectsTable& table) : NeutralEffect(is, table) {}
	HealEffect(int distance) : NeutralEffect(Effect::HEAL_EFFECT, Info::HEAL, distance) {}
	// TODO heal on game tick
};

class Heal : public Neutral {
public:
	Heal(istream& is, InObjectsTable& table) : Neutral(is, table) {}

	Heal() : Neutral() {
		texture(&Textures::getInstance().heal());
		effectDistance(4);
	}

	virtual int info() const override {
		return Info::HEAL;
	}

	virtual void onUnitEntered(Unit& unit) override {
		unit.addEffect(new HealEffect(effectDistance()));
	}

	virtual void fillLogInfo(LogInfo& info) override {
		Neutral::fillLogInfo(info);
		info.name = "Heal";
	}
};