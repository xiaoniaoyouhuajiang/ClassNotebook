#pragma once

#include "../Units/units.hpp"

class Game;

typedef enum {
    RULE_REGULAR = 0,
    RULE_DEATHMATCH,
} rule_type;

class GameRule {
public:
    virtual ~GameRule() = default;

    virtual bool can_create_units() = 0;

    virtual void initialize_game(Game* game, unsigned players) = 0;
    virtual void next_player(Game* game) = 0;
    virtual bool is_game_end(Game* game) = 0;

    virtual bool unit_can_move(Game* game, UnitInterface* unit) = 0;

    virtual string get_name() = 0;
};

class GameRuleRegular : public GameRule {
public:
    bool can_create_units();

    void initialize_game(Game* game, unsigned players);
    void next_player(Game* game);
    bool is_game_end(Game* game);

    bool unit_can_move(Game* game, UnitInterface* unit);

    string get_name();
};

class GameRuleDeathmatch : public GameRule {
public:
    bool can_create_units();

    void initialize_game(Game* game, unsigned players);
    void next_player(Game* game);
    bool is_game_end(Game* game);

    bool unit_can_move(Game* game, UnitInterface* unit);

    string get_name();
};
