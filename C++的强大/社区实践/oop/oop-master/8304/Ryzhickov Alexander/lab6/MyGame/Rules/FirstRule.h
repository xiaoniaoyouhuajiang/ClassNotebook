//
// Created by Alex on 11.05.2020.
//

#ifndef GAME_FIRSTRULE_H
#define GAME_FIRSTRULE_H


#include "Rule.h"
class Unit;

class FirstRule : public Rule {
public:
    void getStartUnitPack (int *arrayUnit) override ;
    int getStartMoney () override ;
    int getOrder() override ;
    bool checkEndGame(int *unitMoneyAdress1, int *unitMoneyAdress2);
};


#endif //GAME_FIRSTRULE_H
