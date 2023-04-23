//
// Created by Artem Butko on 24.05.2020.
//

#include "RuleOne.h"

Field *RuleOne::createField(int players)
{
    field = new Field(10, 10, players);
    field->createBase(0, 0, 5, 'B', 0);
    field->createBase(8, 8, 5, 'D', 1);
    if (players == 3) field->createBase(8, 0, 5, 'U', 2);
    this->players = players;
    return field;
}

int RuleOne::isLose(Field *field)
{
    if(!field) return -1;
    if (field->basesOnField[0] == nullptr || field->basesOnField[1] == nullptr) return -1;
    if (players == 3 && field->basesOnField[2] == nullptr) return  - 1;
    if (field->basesOnField[0]->health.get() <= 0) return 0;
    if (field->basesOnField[1]->health.get() <= 0) return 1;
    if (players == 3 && field->basesOnField[2]->health.get() <= 0) return 2;
    return -1;
}

void RuleOne::playerCommand(std::string command, Chain *player)
{
    currentPlayer->playerCommand(command, player);
    if (command == "/move" || command == "/create" || command == "/get" || command == "/attack" || command == "/skip") changeState();
}
