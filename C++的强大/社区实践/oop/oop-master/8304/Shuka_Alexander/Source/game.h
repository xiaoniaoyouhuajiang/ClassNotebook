#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <math.h>

#include "Field/gamefield.h"

#include "facade.h"

#include "Logger/consolelogger.h"
#include "Logger/filelogger.h"
#include "Logger/unitlogmsg.h"
#include "Logger/playerlogmsg.h"

#include "Snapshot/snapshot.h"


enum class COMMAND : int
{
    NO_COMMAND,
    CRT_GROUND,
    CRT_FLYING,
    CRT_STANDING,
    ATTACK,
    DEFFEND,
    EXIT,
    SAVE,
    LOAD
};


class Game
{
    friend Snapshot;

public:
    explicit Game();
    void run();

private:
    void init();
    void createField();
    void draw() const;
    void farmEnemy();
    void farmPlayer();
    bool logic(COMMAND command = COMMAND::NO_COMMAND);
    void enemyLogic();
    COMMAND input();

private:
    bool isRun;
    std::shared_ptr<Logger> logger;
    std::shared_ptr<Mediator> mediator;
    std::shared_ptr<GameField> field;
    std::shared_ptr<std::set<std::shared_ptr<unit::Unit>>> playerUnits;
    std::shared_ptr<std::set<std::shared_ptr<unit::Unit>>> enemyUnits;
    std::shared_ptr<unit::Base> playerBase;
    std::shared_ptr<unit::Base> enemyBase;
    std::shared_ptr<Facade> enemyFacade;
    std::shared_ptr<Facade> playerFacade;
    size_t playerGold;
    size_t enemyGold;
    std::shared_ptr<RandomObjectFactory> factory;
    bool isPlayerAttack;
};

#endif // GAME_H
