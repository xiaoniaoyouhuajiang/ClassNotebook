#pragma once

#include <vector>
#include "LoggerProxy.h"


class LogAdapter
{
public:
    LogAdapter(uint16_t loggingDirection, uint16_t loggingMode);
    ~LogAdapter();

    void setLoggingMode(uint16_t loggingMode);
    void setLoggingDirection(uint16_t loggingDirection);

    void log(uint16_t logType, std::vector<int>& parameters);

private:
    std::string gameCreatedMessage(std::vector<int>& parameters);
    std::string gameDeletedMessage(std::vector<int>& parameters);
    std::string gameTurnMessage(std::vector<int>& parameters);

    std::string objectTypeToString(int unitType);

    std::string playerObjectCreatedMessage(std::vector<int>& parameters);
    std::string neutralCreatedMessage(std::vector<int>& parameters);

    std::string playerObjectDestructedMessage(std::vector<int>& parameters);
    std::string neutralDestructedMessage(std::vector<int>& parameters);

    std::string moveMessage(std::vector<int>& parameters);
    std::string attackMessage(std::vector<int>& parameters);
    std::string defendMessage(std::vector<int>& parameters);
    std::string takeDamageMessage(std::vector<int>& parameters);
    std::string unificationMessage(std::vector<int>& parameters);
    std::string produceMessage(std::vector<int>& parameters);

    std::string neutralSmallHealMessage(std::vector<int>& parameters);
    std::string neutralFullHealMessage(std::vector<int>& parameters);
    std::string neutralAttackMessage(std::vector<int>& parameters);
    std::string neutralArmorMessage(std::vector<int>& parameters);
    std::string neutralMovesMessage(std::vector<int>& parameters);

    std::string userTurnMessage(std::vector<int>& parameters);
    std::string selectMessage(std::vector<int>& parameters);
    std::string unselectMessage(std::vector<int>& parameters);
    std::string userMoveMessage(std::vector<int>& parameters);
    std::string userAttackMessage(std::vector<int>& parameters);
    std::string userUniteMessage(std::vector<int>& parameters);
    std::string userProduceMessage(std::vector<int>& parameters);

    LoggerProxy* logger;
    uint16_t loggingMode;
};


enum LoggingMode {
    LOGGING_MODE_DEFAULT,
    LOGGING_MODE_ODD,
};

enum LogType {
    LOG_GAME_CREATED,
    LOG_GAME_DELETED,
    LOG_GAME_TURN,

    LOG_PLOBJECT_CREATED,
    LOG_NEUTRAL_CREATED,

    LOG_PLOBJECT_DESTRUCTED,
    LOG_NEUTRAL_DESTRUCTED,

    LOG_MOVE,
    LOG_ATTACK,
    LOG_DEFEND,
    LOG_TAKE_DAMAGE,
    LOG_UNITE,
    LOG_PRODUCE,

    LOG_NEUT_SMALL_HEAL,
    LOG_NEUT_FULL_HEAL,
    LOG_NEUT_ATT_MOD,
    LOG_NEUT_ARM_MOD,
    LOG_NEUT_REN_MOV,

    LOG_USER_TURN,
    LOG_USER_SELECT_OBJECT,
    LOG_USER_UNSELECT_OBJECT,
    LOG_USER_MOVE,
    LOG_USER_ATTACK,
    LOG_USER_UNITE,
    LOG_USER_PRODUCE,
};
