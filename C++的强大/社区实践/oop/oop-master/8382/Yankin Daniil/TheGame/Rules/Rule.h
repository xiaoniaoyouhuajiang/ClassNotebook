#pragma once
#include <utility>
#include <cstdint>
#include <vector>
#include <list>
#include "Trivia/Point.h"

#define WATER_FRAME_SIZE 3

using FieldInit = std::vector<std::vector<uint16_t>>;
using ObjectInit = std::vector<std::pair<Point, uint16_t>>;
using StartInit = std::tuple<FieldInit, ObjectInit, ObjectInit>;

class Rule
{
public:
    Rule(uint16_t playerCount = 2);
    virtual ~Rule() = default;
    void setPlayerCount(uint16_t playerCount);
    virtual StartInit getStartInit(uint16_t width, uint16_t height) = 0;
    virtual std::list<uint16_t> getPlayerOrder() = 0;
    virtual std::pair<bool, std::vector<uint16_t>> checkEndGame() = 0;


protected:
    uint16_t playerCount;
};

enum Rules {
    RULE,
    RULE_ELIMINATION,
    RULE_SPEED,
};

enum InitNames {
    INIT_LAND_ANY,
    INIT_LAND_PASSABLE,
    INIT_LAND_UNPASSABLE,
    INIT_LAND_WATER,

    INIT_NEUTRAL,

    INIT_BLUE_PLAYER,
    INIT_BLUE_BASE,
    INIT_BLUE_UNIT,

    INIT_RED_PLAYER,
    INIT_RED_BASE,
    INIT_RED_UNIT,

    INIT_GREEN_PLAYER,
    INIT_GREEN_BASE,
    INIT_GREEN_UNIT,

    INIT_ORANGE_PLAYER,
    INIT_ORANGE_BASE,
    INIT_ORANGE_UNIT,
};
