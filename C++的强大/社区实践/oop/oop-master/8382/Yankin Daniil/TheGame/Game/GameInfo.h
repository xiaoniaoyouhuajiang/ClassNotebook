#pragma once

#include <cstdint>
#include <typeinfo>
#include <stdexcept>
#include "Rules/EliminationRule.h"
#include "Rules/SpeedRule.h"
#include "Player/Player.h"
#include "Player/PlayerState.h"



class IGameInfo
{
public:
    IGameInfo() : playerContext(nullptr) {}

    virtual ~IGameInfo() {
        delete playerContext;
    }

    void setOrder(std::list<uint16_t>& playerList, uint16_t playerId) {
        delete playerContext;
        playerContext = new PlayerContext(playerList, playerId);
    }

    std::list<uint16_t> getOrder() {
        return playerContext->getOrder();
    }

    void nextPlayerId() {
        playerContext->nextPlayerId();
    }

    uint16_t getPlayerId() const {
        return playerContext->getPlayerId();
    }

    void removePlayerId(uint16_t playerId) {
        playerContext->removePlayerId(playerId);
    }

    virtual StartInit getStartInit(uint16_t width, uint16_t height) = 0;
    virtual std::list<uint16_t> getPlayerOrder() = 0;
    virtual std::pair<bool, std::vector<uint16_t>> checkEndGame() = 0;
    virtual uint16_t getRuleType() = 0;
    virtual uint16_t getPlayerCount() = 0;

protected:
    PlayerContext* playerContext;
};



template<class TemplateRules, uint16_t playerCount>
class GameInfo : public IGameInfo
{
public:
    GameInfo() {
        if (typeid(TemplateRules) != typeid(EliminationRule) && typeid(TemplateRules) != typeid(SpeedRule)) {
            throw std::runtime_error("Incorrect game rules");
        }
        rules = TemplateRules(playerCount);

        auto order = getPlayerOrder();
        playerContext = new PlayerContext(order, order.front());
    }

    ~GameInfo() = default;

    StartInit getStartInit(uint16_t width, uint16_t height) override {
        return rules.getStartInit(width, height);
    }

    std::list<uint16_t> getPlayerOrder() {
        return rules.getPlayerOrder();
    }

    std::pair<bool, std::vector<uint16_t>> checkEndGame() override {
        auto result = rules.checkEndGame();;
        return result;
    }

    uint16_t getRuleType() {
        if (typeid(TemplateRules) == typeid(EliminationRule))
            return RULE_ELIMINATION;
        else
            return RULE_SPEED;
    }

    uint16_t getPlayerCount() {
        return playerCount;
    }

private:
    TemplateRules rules;
};



template<class TemplateRules>
class GameInfo <TemplateRules, 4> : public IGameInfo
{
public:
    GameInfo() {
        if (typeid(TemplateRules) != typeid(EliminationRule) && typeid(TemplateRules) != typeid(SpeedRule)) {
            throw std::runtime_error("Incorrect game rules");
        }
        rules = TemplateRules(4);

        auto order = getPlayerOrder();
        playerContext = new PlayerContext(order, order.front());
    }

    ~GameInfo() = default;

    StartInit getStartInit(uint16_t width, uint16_t height) override {
        return rules.getStartInit(width, height);
    }

    std::list<uint16_t> getPlayerOrder() {
        return rules.getPlayerOrder();
    }

    std::pair<bool, std::vector<uint16_t>> checkEndGame() override {
        auto result = rules.checkEndGame();

        if (result.second.size() >= 3) {
            return result;
        }

        else if (result.second.size() == 1) {
            auto winner = result.second[0];
            std::vector<uint16_t> winners;

            if (winner == PLAYER_BLUE || winner == PLAYER_GREEN) {
                winners.push_back(PLAYER_BLUE);
                winners.push_back(PLAYER_GREEN);
            }
            else if (winner == PLAYER_RED || winner == PLAYER_ORANGE) {
                winners.push_back(PLAYER_RED);
                winners.push_back(PLAYER_ORANGE);
            }

            return std::make_pair(true, winners);
        }

        else if (result.second.size() == 2) {
            if ((result.second[0] == PLAYER_BLUE && result.second[1] == PLAYER_GREEN) || (result.second[0] == PLAYER_GREEN && result.second[1] == PLAYER_BLUE)) {
                return std::make_pair(true, result.second);
            }
            if ((result.second[0] == PLAYER_RED && result.second[1] == PLAYER_ORANGE) || (result.second[0] == PLAYER_ORANGE && result.second[1] == PLAYER_RED)) {
                return std::make_pair(true, result.second);
            }
        }

        return result;
    }

    uint16_t getRuleType() {
        if (typeid(TemplateRules) == typeid(EliminationRule))
            return RULE_ELIMINATION;
        else
            return RULE_SPEED;
    }

    uint16_t getPlayerCount() {
        return 4;
    }

private:
    TemplateRules rules;
};
