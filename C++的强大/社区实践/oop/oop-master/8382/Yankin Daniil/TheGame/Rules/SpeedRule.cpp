#include "SpeedRule.h"
#include "Game/Game.h"
#include "Player/Player.h"
#include "Player/NeutralPlayer.h"
#include "Unit/IUnit.h"
#include <random>

SpeedRule::SpeedRule(uint16_t playerCount) : Rule(playerCount) {}

StartInit SpeedRule::getStartInit(uint16_t width, uint16_t height) {
    FieldInit fieldInit(height);
    for (std::vector<uint16_t>& vector : fieldInit) {
        vector.resize(width, INIT_LAND_ANY);
    }

    for (auto i = 0; i < height; i++) {
        if (i < WATER_FRAME_SIZE || i > height - WATER_FRAME_SIZE) {
            for (auto j = 0; j < width; j++) {
                fieldInit[i][j] = INIT_LAND_WATER;
            }
        }
        else {
            for (auto j = 0; j < WATER_FRAME_SIZE; j++) {
                fieldInit[i][j] = INIT_LAND_WATER;
            }
            for (auto j = width - WATER_FRAME_SIZE; j < width; j++) {
                fieldInit[i][j] = INIT_LAND_WATER;
            }
        }
    }


    ObjectInit players;
    for (auto i = PLAYER + 1; i < PLAYER + 1 + playerCount; i++) {
        uint16_t baseValue;
        if (i == PLAYER_BLUE) {
            baseValue = INIT_BLUE_BASE;
        }
        else if (i == PLAYER_RED) {
            baseValue = INIT_RED_BASE;
        }
        else if (i == PLAYER_GREEN) {
            baseValue = INIT_GREEN_BASE;
        }
        else if (i == PLAYER_ORANGE) {
            baseValue = INIT_ORANGE_BASE;
        }

        while (true) {
            auto randPoint = Point::generatePoint(WATER_FRAME_SIZE, width - WATER_FRAME_SIZE, WATER_FRAME_SIZE, height - WATER_FRAME_SIZE);
            if (fieldInit[randPoint.getY()][randPoint.getX()] == INIT_LAND_ANY) {
                fieldInit[randPoint.getY()][randPoint.getX()] = INIT_LAND_PASSABLE;
                players.push_back(std::make_pair(randPoint, baseValue));
                break;
            }
        }
    }


    ObjectInit neutrals;
    while (true) {
        auto randPoint = Point::generatePoint(WATER_FRAME_SIZE, width - WATER_FRAME_SIZE, WATER_FRAME_SIZE, height - WATER_FRAME_SIZE);
        if (fieldInit[randPoint.getY()][randPoint.getX()] == INIT_LAND_ANY) {
            fieldInit[randPoint.getY()][randPoint.getX()] = INIT_LAND_PASSABLE;
            neutrals.push_back(std::make_pair(randPoint, INIT_NEUTRAL));
            break;
        }
    }

    for (unsigned int i = 0; i < players.size(); i++) {
        auto basePoint = players[i].first;
        auto neutralPoint = neutrals[0].first;

        if (basePoint.getX() < neutralPoint.getX()) {
            auto x = basePoint.getX();
            while (x < neutralPoint.getX()) {
                fieldInit[basePoint.getY()][x] = INIT_LAND_PASSABLE;
                x++;
            }
        }
        else if (basePoint.getX() > neutralPoint.getX()) {
            auto x = basePoint.getX();
            while (x < neutralPoint.getX()) {
                fieldInit[basePoint.getY()][x] = INIT_LAND_PASSABLE;
                x--;
            }
        }

        if (basePoint.getY() < neutralPoint.getY()) {
            auto y = basePoint.getY();
            while (y < neutralPoint.getY()) {
                fieldInit[y][basePoint.getX()] = INIT_LAND_PASSABLE;
                y++;
            }
        }
        else if (basePoint.getY() > neutralPoint.getY()) {
            auto y = basePoint.getY();
            while (y < basePoint.getY()) {
                fieldInit[y][neutralPoint.getX()] = INIT_LAND_PASSABLE;
                y--;
            }
        }
    }

    return std::make_tuple(fieldInit, players, neutrals);
}

std::list<uint16_t> SpeedRule::getPlayerOrder() {
    std::vector<uint16_t> orderVector;
    for (uint16_t id = PLAYER_BLUE; id < PLAYER_BLUE + playerCount; id++) {
        orderVector.push_back(id);
    }
    std::random_shuffle(orderVector.begin(), orderVector.end());

    std::list<uint16_t> order;
    for (auto id : orderVector) {
        order.push_back(id);
    }
    return order;
}

std::pair<bool, std::vector<uint16_t>> SpeedRule::checkEndGame() {
    bool result = false;
    std::vector<uint16_t> winners;
    Game& game = Game::getInstance();

    auto player = game.neutralPlayer;
    for (auto neutral : player->neutralSet) {
        auto point = neutral->getPoint();

        if (!game.field->isUnitFree(point)) {
            auto unit = game.field->getUnit(point);

            bool check = false;
            for (auto winner : winners) {
                if (winner == unit->getPlayer()->getColor()) {
                    check = true;
                }
            }
            if (!check) {
                winners.push_back(unit->getPlayer()->getColor());
                if (winners.size() == 1) {
                    result = true;
                }
                else {
                    result = false;
                }
            }
        }

    }

    return std::make_pair(result, winners);
}
