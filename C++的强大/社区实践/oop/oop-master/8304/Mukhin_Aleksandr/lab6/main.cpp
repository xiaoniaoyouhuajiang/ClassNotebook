#include <iostream>
#include "Rule.h"
#include "EasyRule.h"
#include <memory>
#include "HardRule.h"
#include "Game.hpp"

int main() {
    std::shared_ptr<Rule> rule = std::make_shared<HardRule>();
    Game<Rule>* game = Game<Rule>::get_game(rule);
    Boardfield a;
    Base b;
    game->init(a, b);
    game->play(a, b);
    return 0;
}
