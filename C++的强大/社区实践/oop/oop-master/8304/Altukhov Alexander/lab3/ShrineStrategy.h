#pragma once
#include "Strategy.h"
class ShrineStrategy : public Strategy {

public:
	virtual void applyEffect(Unit*& target);
	virtual void removeEffect(Unit*& target);
	virtual void applyEffectForTimur(Unit& target);
	virtual void removeEffectForTimur(Unit& target);
};

