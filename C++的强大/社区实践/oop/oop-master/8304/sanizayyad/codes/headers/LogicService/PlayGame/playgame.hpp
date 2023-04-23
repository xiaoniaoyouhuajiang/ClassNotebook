#ifndef playgame_hpp
#define playgame_hpp

#include "facade.hpp"
#include "base.hpp"
#include "BattleField.hpp"
#include "originator.hpp"
#include "caretaker.hpp"
#include "proxy.hpp"
#include "rule1.hpp"
#include "rule2.hpp"
#include "context.hpp"
#include "action.hpp"

#include <math.h>
#include <iostream>
#include <stdio.h>



class PlayGame
{
    friend Originator;
public:
    
    void startGame();
    //should not be cloneable
    PlayGame(PlayGame &other) = delete;
    //should not be assignable
    void operator=(const PlayGame &) = delete;
    
    static PlayGame *GetInstance(std::shared_ptr<Rules> gameRules, int numPlayers);

protected:
    PlayGame(std::shared_ptr<Rules> gameRules, int numPlayers);
    

private:
    void initiliaze();
    void createBattleField();
    void printGame() const;
    bool actionLogic(ACTION action = ACTION::NO_ACTION, int playerQue = 1);
    void computerLogic();
    ACTION input();
    bool winCondition(int type);


private:
    static PlayGame* playGameSingleton;
    std::shared_ptr<Rules> gameRules;
    int numPlayers;
    
    bool isRunning;
    std::shared_ptr<Mediator> mediator;
    std::shared_ptr<BattleField> battleField;
    std::shared_ptr<std::set<std::shared_ptr<Unit>>> playerUnits;
    std::shared_ptr<std::set<std::shared_ptr<Unit>>> enemyUnits;
    std::shared_ptr<Base> playerBase;
    std::shared_ptr<Base> enemyBase;
    std::shared_ptr<Facade> enemyFacade;
    std::shared_ptr<Facade> playerFacade;
    std::shared_ptr<Proxy> proxyLog;
    std::shared_ptr<Originator> originator;
    std::shared_ptr<Caretaker> careTaker;
    Context* playerStateContext;
    
    bool isPlayerAttack;
    int numberOfUsersAllowed;
    int numberOfEnemiesAllowed;
    int dead;
};

#endif /* playgame_hpp */
