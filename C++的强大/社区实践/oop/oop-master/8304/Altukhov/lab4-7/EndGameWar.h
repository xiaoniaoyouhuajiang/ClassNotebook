#pragma once
#include "Base.h"
class EndGameWar
{

public:
	static int checkGameEnd(Base*& base1, Base*& base2) {
		if (base1->getHp() <= 0 || base2->getHp() <= 0) {
			return base1->getHp() > 0? 1 : 2;
		}
		return 0;
	}
};

