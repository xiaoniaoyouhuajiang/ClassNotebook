#include "Game.h"
#include "Player/Player.h"
#include "Player/NeutralPlayer.h"
#include "Base/Base.h"
#include "Rules/Rule.h"

int Game::Initializer::initialize(uint16_t playerCount, uint16_t width, uint16_t height, StartInit& startInit) {
    Game& game = Game::getInstance();
    game.field = new Field(width, height, std::get<0>(startInit));


    for (uint16_t id = PLAYER_BLUE; id < PLAYER_BLUE + playerCount; id++) {
        game.playerVector.push_back(new Player(id));
    }

    auto playerInit = std::get<1>(startInit);
    Base* lastBase = nullptr;
    for (auto objectPair : playerInit) {
        auto point = objectPair.first;
        auto type = objectPair.second;

        if (type == INIT_BLUE_BASE) {
            auto player = game.getPlayerOfColor(PLAYER_BLUE);
            auto base = new Base(point, player);
            game.field->setBase(point, base);
            lastBase = base;
        }
        else if (type == INIT_RED_BASE) {
            auto player = game.getPlayerOfColor(PLAYER_RED);
            auto base = new Base(point, player);
            game.field->setBase(point, base);
            lastBase = base;
        }
        else if (type == INIT_GREEN_BASE) {
            auto player = game.getPlayerOfColor(PLAYER_GREEN);
            auto base = new Base(point, player);
            game.field->setBase(point, base);
            lastBase = base;
        }
        else if (type == INIT_ORANGE_BASE) {
            auto player = game.getPlayerOfColor(PLAYER_ORANGE);
            auto base = new Base(point, player);
            game.field->setBase(point, base);
            lastBase = base;
        }
        else if (type == INIT_BLUE_UNIT || type == INIT_RED_UNIT || type == INIT_GREEN_UNIT || type == INIT_ORANGE_UNIT) {
            auto unitType = Unit::generateUnitType();
            UnitFactory factory;
            auto unit = factory.produce(unitType, point, lastBase);
            game.field->setUnit(point, unit);
        }
    }


    game.neutralPlayer = new NeutralPlayer();

    auto neutralInit = std::get<2>(startInit);
    for (auto neutralPair : neutralInit) {
        auto neutral = new NeutralContext(neutralPair.first, game.neutralPlayer);
        game.field->setContext(neutralPair.first, neutral);
    }

    return 0;
}
