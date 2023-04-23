#ifndef OOP_GAME_H
#define OOP_GAME_H

#include <iostream>
#include <algorithm>
#include <unistd.h>
#include <sstream>
#include "Logger.h"
#include "World.h"


class Game;

class MenuFacade{
    Base* base;
public:
    MenuFacade& setBase(Base* b);
    Base& getBase();
    bool isUnitLimit();
    MenuFacade& addUnit(Game& g);
    MenuFacade& delUnit(Game& g);
    MenuFacade& printInfo(Unit* u = NULL);
    MenuFacade& printBase();
};

class Game {
    MenuFacade facade;
    LoggerF logger;
    std::stringstream log;
    char answer;
    World *world;
    char playerName = 0;
    int objectCount = 0;
    int maxObjCount = 0;
    std::pair<int, int> coordPlayer;
    void addWalls();
    void addUnits();
    void delWall();
    void delUnit(int x = 0, int y = 0);
    std::pair<int, int> getUnitCoord();
    void goTo(std::pair<int, int>& from, std::pair<int, int> to);
    void attack(Cell& attacker, Cell& defender);
    void unitRandomWalk();
    std::pair<int, int> findUnit(Unit* u);
    std::pair<int, int> findUnit(int id);
    void mainPlay();
    void menu();
    void goFor(std::pair<int,int> &coordUnit);
    void createPlayerSession();
public:
    Game();
    void printWorld();
    ~Game();
    friend class MenuFacade;
};

#endif //OOP_GAME_H