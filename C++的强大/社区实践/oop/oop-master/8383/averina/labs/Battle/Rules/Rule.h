//
// Created by olyaave on 01.06.2020.
//

#ifndef OOP_RULE_H
#define OOP_RULE_H

#include "../../Field/Field.h"
#include "../States/IState.h"
#include "../../Interface/Links/Chain.h"

class Rule
{
protected:
    Field* field;
    IState* playerOne;
    IState* playerTwo;
    IState* playerThree;
    IState* currentPlayer;
public:
    Rule();
    void changeState();
    char getState();
    virtual Field* createField(int players) = 0;
    virtual void playerCommand(std::string command, Chain *player) = 0;
    int numberOfPlayers;

};

#endif //OOP_RULE_H
