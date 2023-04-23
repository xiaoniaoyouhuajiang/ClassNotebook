//
// Created by Artem Butko on 24.05.2020.
//

#ifndef OOP_NEW_RULE_H
#define OOP_NEW_RULE_H


#include "../../GameField/Field/Field.h"
#include "States/IState.h"
#include "../ChainOfResponsibility/Chain.h"

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


#endif //OOP_NEW_RULE_H
