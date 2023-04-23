//
// Created by Artem Butko on 21.05.2020.
//

#ifndef OOP_NEW_LOGGINGCOMMAND_H
#define OOP_NEW_LOGGINGCOMMAND_H


#include "../../ICommand.h"

/*
 * LoggingCommand -- класс-команда для логирования.
 */

class LoggingCommand : public ICommand
{
public:
    LoggingCommand(Field* field) : ICommand(field) {};
    void Command() override;
};


#endif //OOP_NEW_LOGGINGCOMMAND_H
