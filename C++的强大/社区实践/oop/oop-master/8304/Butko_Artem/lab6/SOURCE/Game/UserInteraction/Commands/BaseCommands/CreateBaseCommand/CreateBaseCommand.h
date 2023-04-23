//
// Created by Artem Butko on 20/05/2020.
//

#ifndef OOP_NEW_CREATEBASECOMMAND_H
#define OOP_NEW_CREATEBASECOMMAND_H


#include "../../ICommand.h"

/*
 * CreateBaseCommand -- класс-команда создания базы.
 */

class CreateBaseCommand : public ICommand
{
public:
    CreateBaseCommand(Field* field) : ICommand(field) {};
    void Command() override;

private:
    int x, y;
    int unitLimit;
};


#endif //OOP_NEW_CREATEBASECOMMAND_H
