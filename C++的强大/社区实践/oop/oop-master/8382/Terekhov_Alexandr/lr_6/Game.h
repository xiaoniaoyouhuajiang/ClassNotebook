#ifndef OOP_GAME_H
#define OOP_GAME_H

#include <iostream>
#include <algorithm>
#include <unistd.h>
#include <sstream>
#include "Logger.h"
#include "World.h"
#include "Rules.h"



class Game;

class MenuFacade{
    Base* base;
public:
    MenuFacade& setBase(Base* b);
    Base& getBase();
    bool isUnitLimit();
    MenuFacade& addUnit(Game& g);
    MenuFacade& delUnit(Game& g);
    MenuFacade& printInfo(Unit* u = nullptr);
    MenuFacade& printBase();
    MenuFacade& save(Game& g);
    bool load(Game& g);

};


class Game {
    GameRules<RuleEasy> session;
    static Game* game;
    MenuFacade facade;
    LoggerC logger;
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
    bool goTo(std::pair<int, int>& from, std::pair<int, int> to);
    void attack(Cell& attacker, Cell& defender);
    void unitRandomWalk();
    std::pair<int, int> findUnit(Unit* u);
    std::pair<int, int> findUnit(int id);
    void mainPlay();
    void menu();
    bool goFor(std::pair<int,int> &coordUnit);
    void createPlayerSession();
    Game();
    void printWorld();
    void init();
public:
    ~Game();
    static Game* getInstance();
    friend class MenuFacade;
};



#endif //OOP_GAME_H