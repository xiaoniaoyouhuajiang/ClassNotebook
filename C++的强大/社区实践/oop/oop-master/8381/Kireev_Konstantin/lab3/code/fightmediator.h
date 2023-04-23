#pragma once
#include "interfacesforobjects.h"


class FightMediator
{
public:
    void commitFight(UnitInterface* attacker, CreatureInterface* defender)
    {
        attacker->commitAttack(defender);
    }
};
