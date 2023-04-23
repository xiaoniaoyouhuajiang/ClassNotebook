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
    Game(int height, int width, int controlMax, int baseX, int baseY, int controlUnits);

    ~Game();
    void createArcher(int x, int y);
    void createMagician(int x, int y);
    void createElfOnUnicorn(int x, int y);
    void createKnightOnHorse(int x, int y);
    void createKnight(int x, int y);
    void createGnome(int x, int y);

    void moveUnit(int lastX, int lastY, int newX, int newY);
    void attack(int lastX, int lastY, int newX, int newY);
    void printField();

    void createMedicalKit(int x, int y);
    void createPowerPotion(int x, int y);
    void createShild(int x, int y);
    void createStone(int x, int y);

    void infoAboutBase();
};



#endif //UNTITLED_GAME_H
