//
// Created by Artem Butko on 20/05/2020.
//

#ifndef OOP_NEW_ATTACKUNITCOMMAND_H
#define OOP_NEW_ATTACKUNITCOMMAND_H


#include "../../ICommand.h"

/*
 * AttackUnitCommand -- класс-команда атаки юнитом противника.
 */

class AttackUnitCommand : public ICommand
{
public:
    AttackUnitCommand(Field* field, std::string player) : ICommand(field) {this->player = player;};
    void Command() override ;
private:
    int x, y, i, j;
};


#endif //OOP_NEW_ATTACKUNITCOMMAND_H
