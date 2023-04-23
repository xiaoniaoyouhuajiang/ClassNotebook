

#ifndef Game_h
#define Game_h
#include "GameMaster.h"
#include "Rules.h"
#include "Logger.h"

extern std::string logsName;

class GameMaster;
class States;



template <typename Rule> class Game{

protected:
    Game() = default;
    static Game* game;
    GameMaster* gameMaster;
    Rule* rule;
   
public:
    Game(Game& other) = delete;
    void operator=(const Game &) = delete;
    static Game* getInctance();
    void start(mode mode);
};

template <typename Rule>
Game<Rule> *Game<Rule>::game = nullptr;

template <typename Rule>
Game<Rule>* Game<Rule>::getInctance(){
    if(game == nullptr){
        return new Game;
    }
    return game;
}

template <typename Rule>
void Game<Rule>::start(mode mode){
    
    
    gameMaster = new GameMaster;
    rule = new Rule(gameMaster, mode);
    rule->gameProcess();
    delete gameMaster;
};
#endif /* Game_h */


