//
// Created by Alex on 11.05.2020.
//

#ifndef GAME_SECONDRULE_H
#define GAME_SECONDRULE_H


#include "Rule.h"
#include "../Units/Unit.h"

class SecondRule: public Rule {
public:
    void getStartUnitPack (int *arrayUnit) override ;
    int getStartMoney () override ;
    int getOrder() override ;
    bool checkEndGame(Unit *unit,int *adress);
};


#endif //GAME_SECONDRULE_H
