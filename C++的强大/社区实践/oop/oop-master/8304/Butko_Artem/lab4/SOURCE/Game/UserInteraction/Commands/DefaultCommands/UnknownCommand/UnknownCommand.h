//
// Created by Artem Butko on 20/05/2020.
//

#ifndef OOP_NEW_UNKNOWNCOMMAND_H
#define OOP_NEW_UNKNOWNCOMMAND_H


#include "../../ICommand.h"

/*
 * UnknownCommand -- класс-команда для неизвестной команды.
 */

class UnknownCommand : public ICommand
{
public:
    UnknownCommand() : ICommand(nullptr){};
    void Command() override;
};


#endif //OOP_NEW_UNKNOWNCOMMAND_H
