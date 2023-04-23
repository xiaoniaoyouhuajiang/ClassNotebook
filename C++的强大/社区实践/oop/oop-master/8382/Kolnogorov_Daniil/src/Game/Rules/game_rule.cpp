#include "game_rule.hpp"
#include "../game.hpp"
#include <raylib.h>

bool GameRuleRegular::can_create_units() {
    return true;
}

void GameRuleRegular::initialize_game(Game* game, unsigned players) {
    for (unsigned id = 0; id < players; id++) {
        Player* player = new Player(id);
        Coordinates coors = game->field->random_coors();
        Base* base = player->create_base(coors);
        player->set_base(base);
        game->field->place_tile_at(coors, base);
        game->players.push_back(player);
    }

    game->current_player_id = 0;
    game->current_player = game->players[0];
}

void GameRuleRegular::next_player(Game* game) {
    if (is_game_end(game))
        return;

    do {
        game->current_player_id =
            (game->current_player_id + 1) % game->players.size();
        game->current_player = game->players[game->current_player_id];
    } while (!game->current_player->base ||
             game->current_player->base->health == 0);

    for (auto unit : game->current_player->units) {
        unit->reset_status();
    }
}

bool GameRuleRegular::is_game_end(Game* game) {
    unsigned alive_bases = 0;
    for (auto player : game->players) {
        if (player->base && player->base->health != 0) {
            alive_bases++;
        }
    }
    return (alive_bases == 1);
}

bool GameRuleRegular::unit_can_move(Game*, UnitInterface* unit) {
    return !unit->get_moved();
}

string GameRuleRegular::get_name() {
    return "Regular";
}

bool GameRuleDeathmatch::can_create_units() {
    return false;
}

void GameRuleDeathmatch::initialize_game(Game* game, unsigned players) {
    unsigned initial_units = 1;
    for (unsigned id = 0; id < players; id++) {
        Player* player = new Player(id);
        for (unsigned i = 0; i < initial_units; i++) {
            Coordinates coors = game->field->random_coors();
            UnitInterface* unit = random_unit();
            unit->set_owner_id(id);
            unit->set_owner(player);
            game->field->place_unit_at(coors, unit);
            player->add_unit(unit);
        }
        game->players.push_back(player);
    }

    game->current_player_id = 0;
    game->current_player = game->players[0];
}

void GameRuleDeathmatch::next_player(Game* game) {
    if (is_game_end(game))
        return;

    do {
        game->current_player_id =
            (game->current_player_id + 1) % game->players.size();
        game->current_player = game->players[game->current_player_id];
    } while (game->current_player->units.size() == 0);

    for (auto unit : game->current_player->units) {
        unit->reset_status();
    }
}

bool GameRuleDeathmatch::is_game_end(Game* game) {
    unsigned alive_players = 0;
    for (auto player : game->players) {
        if (player->units.size() != 0) {
            alive_players++;
        }
    }
    return (alive_players == 1);
}

bool GameRuleDeathmatch::unit_can_move(Game* game, UnitInterface*) {
    for (auto unit : game->current_player->units) {
        if (unit->get_moved()) {
            return false;
        }
    }
    return true;
}

string GameRuleDeathmatch::get_name() {
    return "Deathmatch";
}
