//
// Created by Artem Butko on 20/05/2020.
//

#ifndef OOP_NEW_CHAIN_H
#define OOP_NEW_CHAIN_H

#include <string>
#include "../../GameField/Field/Field.h"
#include "../Commands/ICommand.h"
#include "../Commands/BaseCommands/BaseInfoCommand/BaseInfoCommand.h"
#include "../Commands/UnitCommands/AttackUnitCommand/AttackUnitCommand.h"
#include "../Commands/UnitCommands/MoveUnitCommand/MoveUnitCommand.h"
#include "../Commands/UnitCommands/CreateUnitCommand/CreateUnitCommand.h"
#include "../Commands/UnitCommands/GetUnitCommand/GetUnitCommand.h"
#include "../Commands/DefaultCommands/UnknownCommand/UnknownCommand.h"
#include "../Commands/DefaultCommands/LoggingCommand/LoggingCommand.h"
#include "../Commands/DefaultCommands/GameSaveCommand/GameSaveCommand.h"
#include "../Commands/DefaultCommands/SkipCommand/SkipCommand.h"
#include "../../Exсeptions/Logical/LogicalError.h"
#include "../../Exсeptions/OutOfRange/OutOfRangeError.h"
#include "../../Exсeptions/Type/TypeError.h"

/*
 * Chain -- класс для реализации паттерна "Цепочка обязанностей".
 */

class Chain
{
private:
    Chain* next;
protected:
    Chain(Field* field);
    Field* field;
public:
    Chain();
    void setNext(Chain* link);
    void addNext(Chain* link);
    virtual void chain(std::string command, std::string player);
};


#endif //OOP_NEW_CHAIN_H
