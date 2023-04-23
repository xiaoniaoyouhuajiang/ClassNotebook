#pragma once     
#include "map.hpp"
#include "objectstorage.hpp"
#include "base.hpp"
#include "logger.hpp"

class Rule {
public:
    Rule(int maxUnits, int movesOnIter, char firstMove) : maxUnits(maxUnits), movesOnIter(movesOnIter),
    firstMove(firstMove) {}
    int getMaxUnits();
    int getMovesOnIter();
    int getWhosFirst();
    virtual char win(RadiantBase* radiant, DireBase* dire) = 0;
protected:
    int maxUnits;
    int movesOnIter;
    char firstMove;
};

class FirstRule : public Rule {
public:
    FirstRule() : Rule(5, 3, 1) {}
    virtual char win(RadiantBase* radiant, DireBase* dire);
};

class SecondRule : public Rule {
public:
    SecondRule() : Rule(10, 5, 1) {}
    virtual char win(RadiantBase* radiant, DireBase* dire);
};

template <typename ConcreteRule>
class GameRules {
public:
    GameRules() : rule(new ConcreteRule()) {}
    char check(RadiantBase* radiant, DireBase* dire) {return rule->win(radiant, dire);}
    ConcreteRule* getRule() {return rule;}
    ~GameRules() {delete rule;}
private:
    ConcreteRule* rule;
};


class GameController {
    friend class GameSingleton;
    public:
        void moveObject(Object* au, std::shared_ptr<MapCell> map_cell);
        ~GameController();
        GameController& operator=(const GameController &gc) = delete;
        GameController(const GameController &gc) = delete;
        Map* getMap();
        ObjectStorage* getObjectStorage();
        Base* getCurrentBase();
        DireBase* getDireBase();
        RadiantBase* getRadiantBase();
        void setBase(Base* newBase);
        Unit* getCurrentHero();
        void setCurrentHero(Unit* newHero);
        void setLogger(Logger* newLogger);
        Logger* getLogger();
        GameRules<FirstRule>* getRules();
    protected:
        GameController(uint32_t map_width = 20, uint32_t map_height = 20);
    private:
        Map* map;
        ObjectStorage* objectStorage;
        DireBase* dire;
        RadiantBase* radiant;
        Base* currentBase;
        Unit* currentHero;
        Logger* logger = new TerminalLogger();
        GameRules<FirstRule>* rules;
};

class GameSingleton {
    public:
        static GameController* getGameController(uint32_t map_width = 10, uint32_t map_height = 10);
        static void deleteGameController();
    protected:
        static GameController* gc;
};