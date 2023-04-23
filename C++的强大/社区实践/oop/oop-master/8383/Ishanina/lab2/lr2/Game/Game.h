//
// Created by Mila
//

#ifndef UNTITLED_GAME_H
#define UNTITLED_GAME_H


#include "../Field/Field.h"
#include "../Base/Base.h"
//методы: добавить юнита 6 штук
//метод мув и аттак
class Game {
Field* field;
Base* base;
Unit** units;//храним массив указателей юнитов
int counter;//счетчик баз
public:
    Game();

    ~Game();

};



#endif //UNTITLED_GAME_H
