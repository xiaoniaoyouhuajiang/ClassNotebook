//
// Created by Artem Butko on 20/05/2020.
//

#ifndef OOP_NEW_GETUNITCOMMAND_H
#define OOP_NEW_GETUNITCOMMAND_H


#include "../../ICommand.h"

/*
 * GetUnitCommand -- класс-команда создания юнита.
 */

class GetUnitCommand : public ICommand
{
public:
    GetUnitCommand(Field* field) : ICommand(field) {}
    void Command() override ;
private:
    char id;
    int x, y;
};


#endif //OOP_NEW_GETUNITCOMMAND_H
