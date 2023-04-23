#include "EliminationRule.h"
#include "Game/Game.h"
#include "Player/Player.h"

EliminationRule::EliminationRule(uint16_t playerCount) : Rule(playerCount) {}

StartInit EliminationRule::getStartInit(uint16_t width, uint16_t height) {
    FieldInit fieldInit(height);
    for (std::vector<uint16_t>& vector : fieldInit) {
        vector.resize(width, INIT_LAND_ANY);
    }

    for (auto i = 0; i < height; i++) {
        if (i < WATER_FRAME_SIZE || i >= height - WATER_FRAME_SIZE) {
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
    ObjectInit neutrals;
    for (uint16_t i = PLAYER + 1; i < PLAYER + 1 + playerCount; i++) {
        uint16_t baseValue, unitValue;
        if (i == PLAYER_BLUE) {
            baseValue = INIT_BLUE_BASE;
            unitValue = INIT_BLUE_UNIT;
        }
        else if (i == PLAYER_RED) {
            baseValue = INIT_RED_BASE;
            unitValue = INIT_RED_UNIT;
        }
        else if (i == PLAYER_GREEN) {
            baseValue = INIT_GREEN_BASE;
            unitValue = INIT_GREEN_UNIT;
        }
        else if (i == PLAYER_ORANGE) {
            baseValue = INIT_ORANGE_BASE;
            unitValue = INIT_ORANGE_UNIT;
        }

        for (auto j = 0; j < 2; j++) {
            while (true) {
                auto randPoint = Point::generatePoint(WATER_FRAME_SIZE, width - WATER_FRAME_SIZE, WATER_FRAME_SIZE, height - WATER_FRAME_SIZE);
                if (fieldInit[randPoint.getY()][randPoint.getX()] == INIT_LAND_ANY) {
                    fieldInit[randPoint.getY()][randPoint.getX()] = INIT_LAND_PASSABLE;
                    players.push_back(std::make_pair(randPoint, baseValue));
                    break;
                }
            }
            while (true) {
                auto randPoint = Point::generatePoint(WATER_FRAME_SIZE, width - WATER_FRAME_SIZE, WATER_FRAME_SIZE, height - WATER_FRAME_SIZE);
                if (fieldInit[randPoint.getY()][randPoint.getX()] == INIT_LAND_ANY) {
                    fieldInit[randPoint.getY()][randPoint.getX()] = INIT_LAND_PASSABLE;
                    players.push_back(std::make_pair(randPoint, unitValue));
                    break;
                }
            }
        }

        while (true) {
            auto randPoint = Point::generatePoint(WATER_FRAME_SIZE, width - WATER_FRAME_SIZE, WATER_FRAME_SIZE, height - WATER_FRAME_SIZE);
            if (fieldInit[randPoint.getY()][randPoint.getX()] == INIT_LAND_ANY) {
                fieldInit[randPoint.getY()][randPoint.getX()] = INIT_LAND_PASSABLE;
                neutrals.push_back(std::make_pair(randPoint, INIT_NEUTRAL));
                break;
            }
        }
    }

    auto pointOne = players[0].first;
    auto pointTwo = pointOne;
    for (unsigned int i = 0; i < players.size(); i += 2) {
        pointOne = pointTwo;
        pointTwo = players[i].first;

        if (pointOne.getX() < pointTwo.getX()) {
            auto x = pointOne.getX();
            while (x < pointTwo.getX()) {
                fieldInit[pointOne.getY()][x] = INIT_LAND_PASSABLE;
                x++;
            }
        }
        else if (pointOne.getX() > pointTwo.getX()) {
            auto x = pointOne.getX();
            while (x > pointTwo.getX()) {
                fieldInit[pointOne.getY()][x] = INIT_LAND_PASSABLE;
                x--;
            }
        }

        if (pointOne.getY() < pointTwo.getY()) {
            auto y = pointOne.getY();
            while (y < pointTwo.getY()) {
                fieldInit[y][pointOne.getX()] = INIT_LAND_PASSABLE;
                y++;
            }
        }
        else if (pointOne.getY() > pointTwo.getY()) {
            auto y = pointOne.getY();
            while (y > pointTwo.getY()) {
                fieldInit[y][pointOne.getX()] = INIT_LAND_PASSABLE;
                y--;
            }
        }
    }

    return std::make_tuple(fieldInit, players, neutrals);
}

std::list<uint16_t> EliminationRule::getPlayerOrder() {
    std::list<uint16_t> order;
    for (uint16_t id = PLAYER_BLUE; id < PLAYER_BLUE + playerCount; id++) {
        order.push_back(id);
    }
    return order;
}

std::pair<bool, std::vector<uint16_t>> EliminationRule::checkEndGame() {
    bool result = false;
    std::vector<uint16_t> winners;
    Game& game = Game::getInstance();

    for (auto player : game.playerVector) {
        if (winners.size() == 0 && player->getBaseCount() > 0) {
            winners.push_back(player->getColor());
            result = true;
        }
        else if (winners.size() != 0 && player->getBaseCount() > 0) {
            winners.push_back(player->getColor());
            result = false;
        }
    }
    return std::make_pair(result, winners);
}
