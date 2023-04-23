#pragma once
#include "Base.h"

class GameState {
protected:
	Base* base1;
	Base* base2;
public:
	GameState() {};
	virtual Base*& getRightBase() = 0;
	virtual Base*& getOtherBase() = 0;
};

