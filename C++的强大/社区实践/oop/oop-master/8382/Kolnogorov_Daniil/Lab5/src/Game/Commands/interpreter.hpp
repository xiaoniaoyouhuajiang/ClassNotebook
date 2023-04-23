#pragma once

#include "commands.hpp"
#include <iterator>
#include <string>

class Interpreter {
public:
    Interpreter();
    Command* handle(string command);
    ~Interpreter();

private:
    CommandHandler* next_player_handler;
    CommandHandler* unit_action_handler;
    CommandHandler* create_unit_handler;
    CommandHandler* new_game_handler;
    CommandHandler* end_game_handler;
    CommandHandler* use_powerup_handler;
    CommandHandler* save_game_handler;
    CommandHandler* load_game_handler;
};
