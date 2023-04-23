#pragma once

#include <GAME/engine/Effect.hpp>

class NeutralEffect : public Effect {
private:
	int _neutralInfo;
	int _distance;

public:
	NeutralEffect(EffectName effectName, int neutralInfo, int distance);
	NeutralEffect(const NeutralEffect& from);

	virtual void onOriginMoved(Unit& origin, sf::Vector2i& from, sf::Vector2i& to) override;
	virtual void onOriginDetached(Unit& origin) override;
};
