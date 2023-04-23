//
// Created by Artem Butko on 20/05/2020.
//

#ifndef OOP_NEW_ICOMMAND_H
#define OOP_NEW_ICOMMAND_H


#include "../../GameField/Field/Field.h"

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
};


#endif //OOP_NEW_ICOMMAND_H
