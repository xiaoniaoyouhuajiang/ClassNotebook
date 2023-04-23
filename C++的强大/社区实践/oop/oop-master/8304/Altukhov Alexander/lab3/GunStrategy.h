#pragma once
#include "Strategy.h"
class CannonStrategy : public Strategy {

public:
	virtual void applyEffect(Unit*& target);
	virtual void removeEffect(Unit*& target);
};

