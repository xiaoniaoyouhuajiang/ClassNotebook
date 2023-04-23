//
// Created by Artem Butko on 20/05/2020.
//

#ifndef OOP_NEW_CREATEUNITCOMMAND_H
#define OOP_NEW_CREATEUNITCOMMAND_H


#include "../../ICommand.h"

/*
 * CreateUnitCommand -- класс-команда создания юнита.
 */

class CreateUnitCommand : public ICommand
{
public:
    CreateUnitCommand(Field* field) : ICommand(field) {}
    void Command() override ;
private:
    char id;
};


#endif //OOP_NEW_CREATEUNITCOMMAND_H
