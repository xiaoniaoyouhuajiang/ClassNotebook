#pragma once

#include <GAME/engine/Neutral.hpp>
#include <GAME/utils/Textures.hpp>

class Stone : public Neutral {
public:
	Stone() : Neutral() {
		texture(&Textures::getInstance().stone());
		setFocusable(false);
	}

	virtual int info() const override {
		return Info::STONE;
	}
};