#pragma once
#include "creatures_basic_interfaces.h"
#include "exception.h"


class FightMediator {
public:
    void commitFight(IUnit* attacker, ICreature* defender){

        if(attacker->getPossessorId() == defender->getPossessorId())
            throw new Exception(9, "Irregular attack", "Units can't attack their owner other creatures. So, this attack is impossible");
        else {
            attacker->commitAttack(defender);
        }
    }
};
