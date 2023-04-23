#include <memory>
#include <typeinfo>
#include "Game.h"
#include "GameInfo.h"
#include "Player/Player.h"
#include "Player/NeutralPlayer.h"
#include "Base/Base.h"
#include "Rules/Rule.h"


Game::Loader::Loader(std::string& fileName) {
    stream = std::ifstream(fileName);
    if (!stream.is_open())
        throw std::runtime_error("Open loadFile error") ;
}

Game::Loader::~Loader() {
    stream.close();
}

int Game::Loader::load(Game& game) {
    // !!! Этап считывания файла !!!

    std::string input;
    if (!(stream >> input) || input != "GAME_INFO_START") {
        return 1;
    }

    uint16_t rule, playerCount;
    if (!(stream >> rule >> playerCount)) {
        return 1;
    }
    if (rule != RULE_ELIMINATION && rule != RULE_SPEED) {
        return 1;
    }
    if (playerCount < 2 || playerCount > 4) {
        return 1;
    }

    uint16_t playersAlive;
    if (!(stream >> playersAlive)) {
        return 1;
    }
    if (playersAlive < 2 || playersAlive > playerCount) {
        return 1;
    }

    std::list<uint16_t> playerOrder;
    for (auto i = 0; i < playersAlive; i++) {
        uint16_t color;
        if (!(stream >> color)) {
            return 1;
        }
        if (color < PLAYER_BLUE || color > PLAYER_ORANGE) {
            return 1;
        }
        for (auto elem : playerOrder) {
            if (color == elem) {
                return 1;
            }
        }
        playerOrder.push_back(color);
    }

    uint16_t currentPlayerId;
    if (!(stream >> currentPlayerId)) {
        return 1;
    }
    else {
        bool check = false;
        for (auto elem : playerOrder) {
            if (currentPlayerId == elem) {
                check = true;
                break;
            }
        }
        if (!check) {
            return 1;
        }
    }

    if (!(stream >> input) || input != "GAME_INFO_END") {
        return 1;
    }



    if (!(stream >> input) || input != "FIELD_START") {
        return 1;
    }

    auto FieldSnapshot = std::make_shared<Field::FieldSnapshot>(stream);
    if (!FieldSnapshot->isCorrect()) {
        return 1;
    }

    if (!(stream >> input) || input != "FIELD_END") {
        return 1;
    }


    // Лично я вот от этой строчки просто в шоке, мне плохо, я даже не представляю как назвать переменную
    // Map. Ключ - игрок. Значение - пара векторов с инфой о базах и юнитах + номер базы игрока
    std::vector<std::pair<std::shared_ptr<Player::PlayerSnapshot>, std::pair<std::vector<std::shared_ptr<Base::BaseSnapshot>>, std::vector<std::pair<int,std::shared_ptr<Snapshot>>>>>> playerInfo;
    std::vector<std::shared_ptr<NeutralContext::NeutralSnapshot>> neutralInfo;
    while (true) {
        if (!(stream >> input)) {
            if (playerInfo.size() < 2) {
                return 1;
            }
            for (auto player = playerInfo.begin(); player != playerInfo.end(); player++) {
                if (player->second.first.size() == 0 && player->second.first.size() == 0) {
                    return 1;
                }
            }
            break;
        }

        if (input == "PLAYER_START") {
            auto playerSnaphot = std::make_shared<Player::PlayerSnapshot>(stream);
            if (!playerSnaphot->isCorrect()) {
                return 1;
            }

            for (auto snapshotIter = playerInfo.begin(); snapshotIter != playerInfo.end(); snapshotIter++) {
                if (*(*snapshotIter).first == *playerSnaphot) {
                    return 1;
                }
            }

            bool checkPlayerExist = false;
            for (auto listPlayer : playerOrder) {
                if (playerSnaphot->getColor() == listPlayer) {
                    checkPlayerExist = true;
                }
            }
            if (!checkPlayerExist) {
                return 1;
            }

            std::pair<std::vector<std::shared_ptr<Base::BaseSnapshot>>, std::vector<std::pair<int,std::shared_ptr<Snapshot>>>> tempPair;

            int unitCountAtBase = 0;
            bool playerEnd = false;
            while(!playerEnd) {
                if (!(stream >> input)) {
                    return 1;
                }

                if (input == "BASE_START") {
                    auto baseSnapshot = std::make_shared<Base::BaseSnapshot>(stream);
                    if (!baseSnapshot->isCorrect()) {
                        return 1;
                    }
                    if (!(stream >> input) || input != "BASE_END") {
                        return 1;
                    }
                    tempPair.first.push_back(baseSnapshot);
                    unitCountAtBase = 0;
                }

                else if (input == "UNIT_START") {
                    if (tempPair.first.size() == 0 || unitCountAtBase >= MAX_UNIT_COUNT_AT_BASE) {
                        return 1;
                    }

                    auto unitSnapshot = std::make_shared<Unit::UnitSnapshot>(stream);
                    if (!unitSnapshot->isCorrect()) {
                        return 1;
                    }
                    if (!(stream >> input) || input != "UNIT_END") {
                        return 1;
                    }
                    tempPair.second.push_back(std::make_pair(tempPair.first.size()-1, unitSnapshot));
                    unitCountAtBase++;
                }

                else if (input == "GROUP_START") {
                    if (tempPair.first.size() == 0 || unitCountAtBase >= MAX_UNIT_COUNT_AT_BASE) {
                        return 1;
                    }

                    auto groupSnapshot = std::make_shared<UnitGroup::UnitGroupSnapshot>(stream);
                    if (!groupSnapshot->isCorrect()) {
                        return 1;
                    }
                    if (!(stream >> input) || input != "GROUP_END") {
                        return 1;
                    }
                    tempPair.second.push_back(std::make_pair(tempPair.first.size()-1, groupSnapshot));
                    unitCountAtBase++;
                }

                else if (input == "PLAYER_END") {
                    playerInfo.push_back(std::make_pair(playerSnaphot, tempPair));
                    playerEnd = true;
                }

                else {
                    return 1;
                }
            }
        }

        else if (input == "NEUTRAL_START") {
            auto neutralSnaphot = std::make_shared<NeutralContext::NeutralSnapshot>(stream);
            if (!neutralSnaphot->isCorrect()) {
                return 1;
            }
            if (!(stream >> input) || input != "NEUTRAL_END") {
                return 1;
            }
            neutralInfo.push_back(neutralSnaphot);
        }
    }

    if (playersAlive != playerInfo.size()) {
        return 1;
    }


    // !!! Этап инициализации game !!!

    if (rule == RULE_ELIMINATION) {
        if (playerCount == 2) {
            game.gameInfo = new GameInfo<EliminationRule, 2>();
        }
        else if (playerCount == 3) {
            game.gameInfo = new GameInfo<EliminationRule, 3>();
        }
        else if (playerCount == 4) {
            game.gameInfo = new GameInfo<EliminationRule, 4>();
        }
    }
    else if (rule == RULE_SPEED) {
        if (playerCount == 2) {
            game.gameInfo = new GameInfo<SpeedRule, 2>();
        }
        else if (playerCount == 3) {
            game.gameInfo = new GameInfo<SpeedRule, 3>();
        }
        else if (playerCount == 4) {
            game.gameInfo = new GameInfo<SpeedRule, 4>();
        }
    }

    game.gameInfo->setOrder(playerOrder, currentPlayerId);


    game.field = new Field(*FieldSnapshot);

    for (auto playerPair = playerInfo.begin(); playerPair != playerInfo.end(); playerPair++) {
        auto player = new Player(*playerPair->first);
        game.playerVector.push_back(player);

        auto baseSnapshotVector = playerPair->second.first;
        std::vector<Base*> baseVector;
        for (auto baseSnapshot = baseSnapshotVector.begin(); baseSnapshot != baseSnapshotVector.end(); baseSnapshot++) {
            auto base = new Base(**baseSnapshot, player);
            baseVector.push_back(base);
            if (game.field->setBase(base->getPoint(), base) != 0) {
                clearAfterError(game);
                return 2;
            }
        }

        auto unitPairVector = playerPair->second.second;
        for (auto unitPair = unitPairVector.begin(); unitPair != unitPairVector.end(); unitPair++) {
            int baseIndex = unitPair->first;
            auto base = baseVector[baseIndex];

            auto unitSnapshot = std::dynamic_pointer_cast<Unit::UnitSnapshot>(unitPair->second);
            auto groupSnapshot = std::dynamic_pointer_cast<UnitGroup::UnitGroupSnapshot>(unitPair->second);

            if (unitSnapshot) {
                UnitFactory factory;
                auto unit = factory.produce(*unitSnapshot, base);
                if (game.field->setUnit(unit->getPoint(), unit) != 0) {
                    clearAfterError(game);
                    return 2;
                }
            }
            if (groupSnapshot) {
                auto group = new UnitGroup(*groupSnapshot, base);
                if (game.field->setUnit(group->getPoint(), group) != 0) {
                    clearAfterError(game);
                    return 2;
                }
            }
        }
    }

    game.neutralPlayer = new NeutralPlayer();
    for (auto neutralSnapshot = neutralInfo.begin(); neutralSnapshot != neutralInfo.end(); neutralSnapshot++) {
        auto neutral = new NeutralContext(**neutralSnapshot, game.neutralPlayer);
        if (game.field->setContext(neutral->getPoint(), neutral) != 0) {
            clearAfterError(game);
            return 2;
        }
    }

    return 0;
}

void Game::Loader::clearAfterError(Game& game) {
    for (auto player = game.playerVector.begin(); player != game.playerVector.end(); player++) {
        delete (*player);
    }
    game.playerVector.clear();

    delete game.neutralPlayer;
    game.neutralPlayer = nullptr;

    delete game.field;
    game.field = nullptr;
}
