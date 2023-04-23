#pragma once
#include "creatures_basic_interfaces.h"


class FightMediator {
public:
    void commitFight(IUnit* attacker, ICreature* defender){
        attacker->commitAttack(defender);
    }
};
