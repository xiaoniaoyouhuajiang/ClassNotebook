//
// Created by Alex on 11.05.2020.
//

#ifndef GAME_RULE_H
#define GAME_RULE_H


class Rule {
public:
    virtual void getStartUnitPack (int *arrayUnit) = 0;
    virtual int getStartMoney () = 0;
    virtual int getOrder() = 0;
};


#endif //GAME_RULE_H
