//
// Created by Artem Butko on 20/05/2020.
//

#ifndef OOP_NEW_BASEINFOCOMMAND_H
#define OOP_NEW_BASEINFOCOMMAND_H


#include "../../ICommand.h"

/*
 * BaseInfoCommand -- класс-команда получения информации от базы.
 */

class BaseInfoCommand : public ICommand
{
public:
    BaseInfoCommand(Field* field, std::string player) : ICommand(field) {this->player = player;};
    void Command() override;
};


#endif //OOP_NEW_BASEINFOCOMMAND_H
