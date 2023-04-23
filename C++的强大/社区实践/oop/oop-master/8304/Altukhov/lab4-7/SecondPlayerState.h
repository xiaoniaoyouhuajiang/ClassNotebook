#pragma once
#include "GameState.h"

class SecondPlayerState :
	public GameState
{
public:
	SecondPlayerState(Base*& base, Base*& otherBase) {
		base2 = base;
		base1 = otherBase;
	}
	virtual Base*& getRightBase() {
		return base2;
	}
	virtual Base*& getOtherBase() {
		return base1;
	}
};