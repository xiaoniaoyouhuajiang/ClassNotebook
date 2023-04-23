#pragma once

#include "../game.hpp"

class Coordinates;
class UnitFactory;

class Command {
protected:
    Game* game;

public:
    virtual void execute() = 0;
};

class CommandNewGame : public Command {
public:
    CommandNewGame(Game* game, unsigned width, unsigned height,
                   unsigned players)
        : game(game), width(width), height(height), players(players) {}
    void execute() override { game->new_game(width, height, players); }

private:
    Game* game;
    unsigned width;
    unsigned height;
    unsigned players;
};

class CommandEndGame : public Command {
public:
    CommandEndGame(Game* game) : game(game) {}
    void execute() override { game->end_game(); }

private:
    Game* game;
};

class CommandNextPlayer : public Command {
public:
    CommandNextPlayer(Game* game) : game(game) {}
    void execute() override { game->next_player(); }

private:
    Game* game;
};

class CommandUnitAction : public Command {
public:
    CommandUnitAction(Game* game, Coordinates from_coors, Coordinates to_coors)
        : game(game), from_coors(from_coors), to_coors(to_coors) {}
    void execute() override { game->unit_action(from_coors, to_coors); }

private:
    Game* game;
    Coordinates from_coors;
    Coordinates to_coors;
};

class CommandCreateUnit : public Command {
public:
    CommandCreateUnit(Game* game, Coordinates coors, UnitFactory* factory)
        : game(game), coors(coors), factory(factory) {}
    void execute() override { game->create_unit(coors, factory); }

private:
    Game* game;
    Coordinates coors;
    UnitFactory* factory;
};
