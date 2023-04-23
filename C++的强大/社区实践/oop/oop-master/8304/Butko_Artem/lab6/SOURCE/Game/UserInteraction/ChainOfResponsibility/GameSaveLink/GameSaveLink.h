//
// Created by Artem Butko on 22.05.2020.
//

#ifndef OOP_NEW_GAMESAVELINK_H
#define OOP_NEW_GAMESAVELINK_H


#include "../Chain.h"

/*
 * GameSaveLink -- класс-звено цепи для сохранения и загрузки игрового поля.
 */

class GameSaveLink : public Chain
{
public:
    GameSaveLink(Field* field) : Chain(field) {};
    void chain(std::string command, std::string player) override;
};


#endif //OOP_NEW_GAMESAVELINK_H
