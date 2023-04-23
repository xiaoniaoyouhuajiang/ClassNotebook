#ifndef LABOOP_GAME_HPP
#define LABOOP_GAME_HPP

#include "Facade.hpp"

template <typename Rule>
class Game {
public:
    explicit Game(Rule *rules) : rules(rules) {
        facade = new Facade();
    };
    void startGame() {
        facade->startGame(rules);
        facade->makeAction();}
    ~Game()= default;
private:
    Rule *rules;
    Facade *facade;
};



#endif //LABOOP_GAME_HPP
