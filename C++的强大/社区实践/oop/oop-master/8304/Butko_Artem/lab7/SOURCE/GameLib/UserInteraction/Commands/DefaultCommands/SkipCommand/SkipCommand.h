//
// Created by Artem Butko on 30.05.2020.
//

#ifndef OOP_NEW_SKIPCOMMAND_H
#define OOP_NEW_SKIPCOMMAND_H


#include "../../ICommand.h"

class SkipCommand : public ICommand
{
public:
    SkipCommand(Field* field, std::string player) : ICommand(field) {this->player = player;}
    void Command() override;
};


#endif //OOP_NEW_SKIPCOMMAND_H
