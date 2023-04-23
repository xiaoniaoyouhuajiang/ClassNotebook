#pragma once

#include <cstdint>
#include <fstream>
#include <set>
#include "Trivia/Snapshot.h"
#include "Game/Game.h"

class IUnit;
class Base;
class NeutralContext;


class Player
{
    friend class Game;
    friend class Game::Saver;
    friend class GameFacade;

public:
    class PlayerSnapshot;

    Player(uint16_t color);
    Player(PlayerSnapshot& snapshot);
    ~Player();
    uint16_t getColor();

    void addUnit(IUnit* unit);
    void removeUnit(IUnit* unit);

    void addBase(Base* base);
    void removeBase(Base* base);

    int getBaseCount();
    int getUnitCount();

private:
    std::set <IUnit*>* getUnitSet();
    std::set <Base*>* getBaseSet();

    uint16_t color;

    std::set <IUnit*> unitSet;
    std::set <Base*> baseSet;
};


class Player::PlayerSnapshot : public Snapshot {
    friend class Player;

public:
    PlayerSnapshot(Player& player);
    PlayerSnapshot(std::ifstream& stream);
    uint16_t getColor() const;
    friend std::ofstream& operator<<(std::ofstream& stream, const Player::PlayerSnapshot& snapshot);
    friend bool operator==(Player::PlayerSnapshot& snapshot1, Player::PlayerSnapshot& snapshot2);
    friend bool operator!=(Player::PlayerSnapshot& snapshot1, Player::PlayerSnapshot& snapshot2);

private:
    uint16_t color;
};


enum PlayerColors {
    PLAYER,
    PLAYER_BLUE,
    PLAYER_RED,
    PLAYER_GREEN,
    PLAYER_ORANGE,
};
