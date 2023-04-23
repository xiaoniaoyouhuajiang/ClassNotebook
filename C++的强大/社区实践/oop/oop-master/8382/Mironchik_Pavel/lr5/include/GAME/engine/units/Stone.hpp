#pragma once

#include <GAME/engine/Neutral.hpp>
#include <GAME/utils/Textures.hpp>

class Stone : public Neutral {
public:
	Stone(istream& is, InObjectsTable& table) : Neutral(is, table) {}

	Stone() : Neutral() {
		texture(&Textures::getInstance().stone());
		setFocusable(false);
	}

	virtual int info() const override {
		return Info::STONE;
	}

	virtual void fillLogInfo(LogInfo& info) override {
		Neutral::fillLogInfo(info);
		info.name = "Stone";
	}
};