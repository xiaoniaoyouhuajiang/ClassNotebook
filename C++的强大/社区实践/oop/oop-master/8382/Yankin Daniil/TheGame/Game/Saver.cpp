#include <memory>
#include <typeinfo>
#include "Game.h"
#include "GameInfo.h"
#include "Player/Player.h"
#include "Player/NeutralPlayer.h"
#include "Base/Base.h"


Game::Saver::Saver(std::string& fileName) {
    stream = std::ofstream(fileName);
    if (!stream.is_open())
        throw std::runtime_error("Open saveFile error") ;
}

Game::Saver::~Saver() {
    stream.close();
}

int Game::Saver::save(Game& game) {
    if (game.field == nullptr) {
        return 1;
    }

    stream << "GAME_INFO_START" << std::endl;
    stream << game.gameInfo->getRuleType() << " " << game.gameInfo->getPlayerCount() << std::endl;
    auto order = game.gameInfo->getOrder();
    stream << order.size();
    for (auto player : order) {
        stream << " " << player;
    }
    stream << std::endl << game.gameInfo->getPlayerId()  << std::endl;
    stream << "GAME_INFO_END" << std::endl << std::endl;

    stream << "FIELD_START" << std::endl;
    auto fieldSnapshot = std::make_shared<Field::FieldSnapshot>(*game.field);
    stream << *fieldSnapshot;
    stream << "FIELD_END" << std::endl << std::endl << std::endl;

    for (auto player : game.playerVector) {
        stream << "PLAYER_START" << std::endl;
        auto playerSnapshot = std::make_shared<Player::PlayerSnapshot>(*player);
        stream << *playerSnapshot << std::endl;

        for (auto base : player->baseSet) {
            stream << "BASE_START" << std::endl;
            auto baseSnapshot = std::make_shared<Base::BaseSnapshot>(*base);
            stream << *baseSnapshot;
            stream << "BASE_END" << std::endl << std::endl;

            for (auto unitPointer : base->unitSet) {
                auto unit = dynamic_cast<Unit*>(unitPointer);
                auto group = dynamic_cast<UnitGroup*>(unitPointer);

                if (unit != nullptr) {
                    stream << "UNIT_START" << std::endl;
                    auto unitSnapshot = std::make_shared<Unit::UnitSnapshot>(*unit);
                    stream << *unitSnapshot;
                    stream << "UNIT_END" << std::endl << std::endl;
                }
                else if (group != nullptr) {
                    stream << "GROUP_START" << std::endl;
                    auto groupSnapshot = std::make_shared<UnitGroup::UnitGroupSnapshot>(*group);
                    stream << *groupSnapshot;
                    stream << "GROUP_END" << std::endl << std::endl;
                }
            }
        }

        stream << "PLAYER_END" << std::endl << std::endl << std::endl;
    }

    for (auto neutral : game.neutralPlayer->neutralSet) {
        stream << "NEUTRAL_START" << std::endl;
        auto neutralSnapshot = std::make_shared<NeutralContext::NeutralSnapshot>(*neutral);
        stream << *neutralSnapshot;
        stream << "NEUTRAL_END" << std::endl << std::endl;
    }

    return 0;
}
