#pragma once
#include "Base.h"
class EndGameEconomics
{
public:
	static int checkGameEnd(Base*& base1, Base*& base2) {
		if (base1->getHp() <= 0 || base2->getHp() <= 0) {
			return base1->getHp() > 0 ? 1 : 2;
		}

		if (base1->getTurn() == 11 && base2->getTurn() == 11) {
			return base1->getMoney() > base2->getMoney() ? 1 : 2;
		}
		return 0;
	}
};

