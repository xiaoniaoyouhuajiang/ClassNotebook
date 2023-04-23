#include "interpreter.hpp"
#include "command_create_unit.hpp"
#include "command_end_game.hpp"
#include "command_load_game.hpp"
#include "command_new_game.hpp"
#include "command_next_player.hpp"
#include "command_save_game.hpp"
#include "command_unit_action.hpp"
#include "command_use_neutral.hpp"

Interpreter::Interpreter() {
    unit_action_handler = new UnitActionCommandHandler();
    next_player_handler = new NextPlayerCommandHandler();
    create_unit_handler = new CreateUnitCommandHandler();
    new_game_handler = new NewGameCommandHandler();
    end_game_handler = new EndGameCommandHandler();
    use_powerup_handler = new UseNeutralCommandHandler();
    save_game_handler = new SaveGameCommandHandler();
    load_game_handler = new LoadGameCommandHandler();

    unit_action_handler->set_next(next_player_handler);
    next_player_handler->set_next(create_unit_handler);
    create_unit_handler->set_next(new_game_handler);
    new_game_handler->set_next(end_game_handler);
    end_game_handler->set_next(use_powerup_handler);
    use_powerup_handler->set_next(save_game_handler);
    save_game_handler->set_next(load_game_handler);
}

Command* Interpreter::handle(string command) {
    istringstream iss(command);
    vector<string> cmd(istream_iterator<string>{iss},
                       istream_iterator<string>());
    return unit_action_handler->handle(cmd);
}

Interpreter::~Interpreter() {
    delete unit_action_handler;
    delete next_player_handler;
    delete create_unit_handler;
    delete new_game_handler;
    delete end_game_handler;
    delete use_powerup_handler;
    delete save_game_handler;
    delete load_game_handler;
}
