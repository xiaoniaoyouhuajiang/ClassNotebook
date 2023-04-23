//
// Created by Artem Butko on 20/05/2020.
//

#ifndef OOP_NEW_MOVEUNITCOMMAND_H
#define OOP_NEW_MOVEUNITCOMMAND_H


#include "../../ICommand.h"

/*
 * MoveUnitCommand -- класс-команда создания юнита.
 */

class MoveUnitCommand : public ICommand
{
public:
    MoveUnitCommand(Field* field) : ICommand(field) {};
    void Command() override;
private:
    int x, y, i, j;
};


#endif //OOP_NEW_MOVEUNITCOMMAND_H
