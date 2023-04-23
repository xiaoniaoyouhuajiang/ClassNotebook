//
// Created by Artem Butko on 20/05/2020.
//

#ifndef OOP_NEW_ICOMMAND_H
#define OOP_NEW_ICOMMAND_H


#include "../../GameField/Field/Field.h"
#include "../../Exсeptions/Logical/LogicalError.h"
#include "../../Exсeptions/OutOfRange/OutOfRangeError.h"
#include "../../Exсeptions/Type/TypeError.h"

/*
 * ICommand -- интерфейс паттерна "Команда".
 */

class ICommand
{
public:
    virtual void Command() = 0;

protected:
    ICommand(Field* Field) : field(Field) {};
    Field* field;
    std::string player;
};


#endif //OOP_NEW_ICOMMAND_H
