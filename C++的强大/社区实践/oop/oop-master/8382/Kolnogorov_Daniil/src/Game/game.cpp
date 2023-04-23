#include "game.hpp"
#include "Neutral/neutral_context.hpp"
#include "Neutral/powerup.hpp"

using namespace std;

Game::Game(GameRule* rule) {
    logger = new LoggerProxy();
    field = nullptr;
    // rule = nullptr;
    this->rule = rule;
    current_player = nullptr;
    running = false;
}

Game::~Game() {
    delete logger;
    delete field;
    delete rule;
    for (auto player : players)
        delete player;
}

vector<Coordinates> Game::get_reachable(Coordinates coors) {
    return field->get_reachable(coors);
}

bool Game::unit_can_move(UnitInterface* unit) {
    return rule->unit_can_move(this, unit);
}

bool Game::is_owned_by(unsigned id, UnitInterface* unit) {
    return id == unit->get_owner_id();
}
