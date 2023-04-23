//
// Created by Artem Butko on 22.05.2020.
//

#ifndef OOP_NEW_GAMESAVECOMMAND_H
#define OOP_NEW_GAMESAVECOMMAND_H


#include "../../ICommand.h"

/*
 * GameSaveCommand -- класс-команда для сохранения и загрузки.
 */


class GameSaveCommand : public ICommand
{
public:
    GameSaveCommand(Field* field) : ICommand(field) {};
    void Command() override;
};


#endif //OOP_NEW_GAMESAVECOMMAND_H
