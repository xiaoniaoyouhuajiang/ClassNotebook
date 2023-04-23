#pragma once
#include "GameState.h"

class FirstPlayerState :
	public GameState
{
public:
	FirstPlayerState(Base*& base, Base*& otherBase) {
		base1 = base;
		base2 = otherBase;
	}
	virtual Base*& getRightBase() {
		return base1;
	}
	virtual Base*& getOtherBase() {
		return base2;
	}
};

