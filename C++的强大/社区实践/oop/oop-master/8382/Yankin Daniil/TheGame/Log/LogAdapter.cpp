#include "LogAdapter.h"
#include "Object/Object.h"
#include <string>

LogAdapter::LogAdapter(uint16_t loggingDirection, uint16_t loggingMode) : logger(new LoggerProxy(loggingDirection)), loggingMode(loggingMode) {}

LogAdapter::~LogAdapter() {
    delete logger;
}



void LogAdapter::log(uint16_t logType, std::vector<int>& parameters) {
    std::string info;
    if (logType == LOG_GAME_CREATED) {
        info = gameCreatedMessage(parameters);
    }
    else if (logType == LOG_GAME_DELETED) {
        info = gameDeletedMessage(parameters);
    }
    else if (logType == LOG_GAME_TURN) {
        info = gameTurnMessage(parameters);
    }
    else if (logType == LOG_PLOBJECT_CREATED) {
        info = playerObjectCreatedMessage(parameters);
    }
    else if (logType == LOG_NEUTRAL_CREATED) {
        info = neutralCreatedMessage(parameters);
    }
    else if (logType == LOG_PLOBJECT_DESTRUCTED) {
        info = playerObjectDestructedMessage(parameters);
    }
    else if (logType == LOG_NEUTRAL_DESTRUCTED) {
        info = neutralDestructedMessage(parameters);
    }
    else if (logType == LOG_MOVE) {
        info = moveMessage(parameters);
    }
    else if (logType == LOG_ATTACK) {
        info = attackMessage(parameters);
    }
    else if (logType == LOG_DEFEND) {
        info = defendMessage(parameters);
    }
    else if (logType == LOG_TAKE_DAMAGE) {
        info = takeDamageMessage(parameters);
    }
    else if (logType == LOG_UNITE) {
        info = unificationMessage(parameters);
    }
    else if (logType == LOG_PRODUCE) {
        info = produceMessage(parameters);
    }
    else if (logType == LOG_NEUT_SMALL_HEAL) {
        info = neutralSmallHealMessage(parameters);
    }
    else if (logType == LOG_NEUT_FULL_HEAL) {
        info = neutralFullHealMessage(parameters);
    }
    else if (logType == LOG_NEUT_ATT_MOD) {
        info = neutralAttackMessage(parameters);
    }
    else if (logType == LOG_NEUT_ARM_MOD) {
        info = neutralArmorMessage(parameters);
    }
    else if (logType == LOG_NEUT_REN_MOV) {
        info = neutralMovesMessage(parameters);
    }
    else if (logType == LOG_USER_TURN) {
        info = userTurnMessage(parameters);
    }
    else if (logType == LOG_USER_SELECT_OBJECT) {
        info = selectMessage(parameters);
    }
    else if (logType == LOG_USER_UNSELECT_OBJECT) {
        info = unselectMessage(parameters);
    }
    else if (logType == LOG_USER_MOVE) {
        info = userMoveMessage(parameters);
    }
    else if (logType == LOG_USER_ATTACK) {
        info = userAttackMessage(parameters);
    }
    else if (logType == LOG_USER_UNITE) {
        info = userUniteMessage(parameters);
    }
    else if (logType == LOG_USER_PRODUCE) {
        info = userProduceMessage(parameters);
    }
    logger->log(info);
}

void LogAdapter::setLoggingMode(uint16_t loggingMode) {
    this->loggingMode = loggingMode;
}

void LogAdapter::setLoggingDirection(uint16_t loggingDirection) {
    logger->setLoggingDirection(loggingDirection);
}



std::string LogAdapter::gameCreatedMessage(std::vector<int>& parameters) {
    std::string info;
    if (loggingMode == LOGGING_MODE_DEFAULT)
        info = "Game initialized.";
    else if (loggingMode == LOGGING_MODE_ODD)
        info = "Жители Даларана! Поднимите глаза и взгляните на эту инициализацию игры!";

    info += " Field size: ";
    info += std::to_string(parameters[0]);
    info += "x";
    info += std::to_string(parameters[1]);
    return info;
}

std::string LogAdapter::gameDeletedMessage(std::vector<int>&) {
    std::string info;
    if (loggingMode == LOGGING_MODE_DEFAULT)
        info = "Game deleted";
    else if (loggingMode == LOGGING_MODE_ODD)
        info = "Omae Wa Mou Shindeiru! Nani?";
    return info;
}

std::string LogAdapter::gameTurnMessage(std::vector<int>&) {
    std::string info = "Game turn";
    return info;
}



std::string LogAdapter::objectTypeToString(int unitType) {
    std::string stringType;
    switch (unitType) {
    case UNIT_SWORDSMAN:
        stringType = "SWORDSMAN";
        break;
    case UNIT_PIKEMAN:
        stringType = "PIKEMAN";
        break;
    case UNIT_SHOCK_CAVALRY:
        stringType = "SHOCK CAVALRY";
        break;
    case UNIT_ARCHER:
        stringType = "ARCHER";
        break;
    case UNIT_CROSSBOWMAN:
        stringType = "CROSSBOWMAN";
        break;
    case UNIT_SCOUT_CAVALRY:
        stringType = "SCOUT CAVALRY";
        break;
    case UNIT_CATAPULT:
        stringType = "CATAPULT";
        break;
    case UNIT_RAM:
        stringType = "RAM";
        break;
    case BASE:
        stringType = "BASE";
        break;
    }
    return stringType;
}



std::string LogAdapter::playerObjectCreatedMessage(std::vector<int>& parameters) {
    std::string info;
    if (loggingMode == LOGGING_MODE_DEFAULT)
        info = "Create | ";
    else if (loggingMode == LOGGING_MODE_ODD)
        info = "Сын мой, когда ты родился... | ";
    info += objectTypeToString(parameters[0]) + ". ";
    info += "Position (" + std::to_string(parameters[1]) + "," + std::to_string(parameters[2]) + "). ";
    info += "Player " + std::to_string(parameters[3]);
    return info;
}

std::string LogAdapter::neutralCreatedMessage(std::vector<int>& parameters) {
    std::string info;
    if (loggingMode == LOGGING_MODE_DEFAULT)
        info = "Create | ";
    else if (loggingMode == LOGGING_MODE_ODD)
        info = "Я родился! | ";
    info += "NEUTRAL OBJECT. ";
    info += "Position (" + std::to_string(parameters[0]) + "," + std::to_string(parameters[1]) + "). ";
    return info;
}


std::string LogAdapter::playerObjectDestructedMessage(std::vector<int>& parameters) {
    std::string info;
    if (loggingMode == LOGGING_MODE_DEFAULT)
        info = "Destruct | ";
    else if (loggingMode == LOGGING_MODE_ODD)
        info = "Press F | ";
    info += objectTypeToString(parameters[0]) + ". ";
    info += "Position (" + std::to_string(parameters[1]) + "," + std::to_string(parameters[2]) + "). ";
    info += "Player " + std::to_string(parameters[3]);
    return info;
}

std::string LogAdapter::neutralDestructedMessage(std::vector<int>& parameters) {
    std::string info;
    if (loggingMode == LOGGING_MODE_DEFAULT)
        info = "Destruct | ";
    else if (loggingMode == LOGGING_MODE_ODD)
        info = "Мой взор застилает тьма... | ";
    info += "NEUTRAL OBJECT. ";
    info += "Position (" + std::to_string(parameters[0]) + "," + std::to_string(parameters[1]) + "). ";
    return info;
}


std::string LogAdapter::moveMessage(std::vector<int>& parameters) {
    std::string info;
    if (loggingMode == LOGGING_MODE_DEFAULT)
        info = "Move | ";
    else if (loggingMode == LOGGING_MODE_ODD)
        info = "Еще один юнит добежал до воды! | ";

    info += objectTypeToString(parameters[0]) + ". ";
    info += "Position (" + std::to_string(parameters[1]) + "," + std::to_string(parameters[2]) + "). ";
    info += "Player " + std::to_string(parameters[3]) + " | ";
    info += "New position (" + std::to_string(parameters[4]) + "," + std::to_string(parameters[5]) + ") ";
    return info;
}

std::string LogAdapter::attackMessage(std::vector<int>& parameters) {
    std::string info;
    if (loggingMode == LOGGING_MODE_DEFAULT)
        info = "Attack | ";
    else if (loggingMode == LOGGING_MODE_ODD)
        info = "За Орду! | ";

    info += "Attacker " + objectTypeToString(parameters[0]) + ". ";
    info += "Position (" + std::to_string(parameters[1]) + "," + std::to_string(parameters[2]) + "). ";
    info += "Player " + std::to_string(parameters[3]) + " | ";

    info += "Defender "+ objectTypeToString(parameters[4]) + ". ";
    info += "Position (" + std::to_string(parameters[5]) + "," + std::to_string(parameters[6]) + "). ";
    info += "Player " + std::to_string(parameters[7]) += " | ";

    info += "Damage " + std::to_string(parameters[8]);

    return info;
}

std::string LogAdapter::defendMessage(std::vector<int>& parameters) {
    std::string info;
    if (loggingMode == LOGGING_MODE_DEFAULT)
        info = "Defend | ";
    else if (loggingMode == LOGGING_MODE_ODD)
        info = "За Альянс! | ";

    info += "Defender " + objectTypeToString(parameters[0]) + ". ";
    info += "Position (" + std::to_string(parameters[1]) + "," + std::to_string(parameters[2]) + "). ";
    info += "Player " + std::to_string(parameters[3]) + " | ";

    info += "Attacker "+ objectTypeToString(parameters[4]) + ". ";
    info += "Position (" + std::to_string(parameters[5]) + "," + std::to_string(parameters[6]) + "). ";
    info += "Player " + std::to_string(parameters[7]) += " | ";

    info += "Damage " + std::to_string(parameters[8]);

    return info;
}

std::string LogAdapter::takeDamageMessage(std::vector<int>& parameters) {
    std::string info;
    if (loggingMode == LOGGING_MODE_DEFAULT)
        info = "Take damage | ";
    else if (loggingMode == LOGGING_MODE_ODD)
        info = "Танкую! | ";

    info += objectTypeToString(parameters[0]) + ". ";
    info += "Position (" + std::to_string(parameters[1]) + "," + std::to_string(parameters[2]) + "). ";
    info += "Player " + std::to_string(parameters[3]) + " | ";

    info += "Took "+ std::to_string(parameters[4]) + " damage";

    return info;
}

std::string LogAdapter::unificationMessage(std::vector<int>& parameters) {
    std::string info;
    if (loggingMode == LOGGING_MODE_DEFAULT)
        info = "Unification | ";
    else if (loggingMode == LOGGING_MODE_ODD)
        info = "Мы едины! | ";

    info += objectTypeToString(parameters[0]) + " at position ";
    info += "(" + std::to_string(parameters[1]) + "," + std::to_string(parameters[2]) + ")";
    info += " and ";
    info += "(" + std::to_string(parameters[3]) + "," + std::to_string(parameters[4]) + ")";
    info += " united. ";

    info += "Player " + std::to_string(parameters[5]) + ". ";
    info += "New position (" + std::to_string(parameters[3]) + "," + std::to_string(parameters[4]) + ")";

    return info;
}

std::string LogAdapter::produceMessage(std::vector<int>& parameters) {
    std::string info;
    if (loggingMode == LOGGING_MODE_DEFAULT)
        info = "Produce | ";
    else if (loggingMode == LOGGING_MODE_ODD)
        info = "Опять работать... | ";

    info += "BASE at position ";
    info += "(" + std::to_string(parameters[0]) + "," + std::to_string(parameters[1]) + "). ";
    info += "Player " + std::to_string(parameters[2]) + " | ";
    info += "Produce " + objectTypeToString(parameters[3]);

    return info;
}


std::string LogAdapter::neutralSmallHealMessage(std::vector<int>& parameters) {
    std::string info = "Small Heal | ";

    info += objectTypeToString(parameters[0]) + " at position ";
    info += "(" + std::to_string(parameters[1]) + "," + std::to_string(parameters[2]) + "). ";
    info += "Player " + std::to_string(parameters[3]) + " | ";

    info += "Heal size: " + std::to_string(parameters[4]);

    return info;
}

std::string LogAdapter::neutralFullHealMessage(std::vector<int>& parameters) {
    std::string info = "Full Heal | ";

    info += objectTypeToString(parameters[0]) + " at position ";
    info += "(" + std::to_string(parameters[1]) + "," + std::to_string(parameters[2]) + "). ";
    info += "Player " + std::to_string(parameters[3]);

    return info;
}

std::string LogAdapter::neutralAttackMessage(std::vector<int>& parameters) {
    std::string info = "Attack Mod | ";

    info += objectTypeToString(parameters[0]) + " at position ";
    info += "(" + std::to_string(parameters[1]) + "," + std::to_string(parameters[2]) + "). ";
    info += "Player " + std::to_string(parameters[3]) + " | ";
    info += "Mod size " + std::to_string(parameters[4]);

    return info;
}

std::string LogAdapter::neutralArmorMessage(std::vector<int>& parameters) {
    std::string info = "Armor Mod | ";

    info += objectTypeToString(parameters[0]) + " at position ";
    info += "(" + std::to_string(parameters[1]) + "," + std::to_string(parameters[2]) + "). ";
    info += "Player " + std::to_string(parameters[3]) + " | ";
    info += "Mod size " + std::to_string(parameters[4]);

    return info;
}

std::string LogAdapter::neutralMovesMessage(std::vector<int>& parameters) {
    std::string info = "Renew MovePoints | ";

    info += objectTypeToString(parameters[0]) + " at position ";
    info += "(" + std::to_string(parameters[1]) + "," + std::to_string(parameters[2]) + "). ";
    info += "Player " + std::to_string(parameters[3]);

    return info;
}


std::string LogAdapter::userTurnMessage(std::vector<int>&) {
    std::string info = "User Turn";
    return info;
}

std::string LogAdapter::selectMessage(std::vector<int>& parameters) {
    std::string info;
    if (loggingMode == LOGGING_MODE_DEFAULT)
        info = "Select | ";
    else if (loggingMode == LOGGING_MODE_ODD)
        info = "Как будущий король, я приказываю... | ";

    info += objectTypeToString(parameters[0]) + " at position ";
    info += "(" + std::to_string(parameters[1]) + "," + std::to_string(parameters[2]) + "). ";
    info += "Player " + std::to_string(parameters[3]);

    return info;
}

std::string LogAdapter::unselectMessage(std::vector<int>&) {
    std::string info;
    if (loggingMode == LOGGING_MODE_DEFAULT)
        info = "Unselect";
    else if (loggingMode == LOGGING_MODE_ODD)
        info = "Ты пока что еще не король, юноша!";
    return info;
}

std::string LogAdapter::userMoveMessage(std::vector<int>& parameters) {
    std::string info = "User Move | ";

    info += objectTypeToString(parameters[0]) + " at position ";
    info += "(" + std::to_string(parameters[1]) + "," + std::to_string(parameters[2]) + "). ";
    info += "Player " + std::to_string(parameters[3]) + " | ";

    info += "Move to (" + std::to_string(parameters[4]) + "," + std::to_string(parameters[5]) + ") ";

    return info;
}

std::string LogAdapter::userAttackMessage(std::vector<int>& parameters) {
    std::string info = "User Attack | ";

    info += "Attacker " + objectTypeToString(parameters[0]) + ". ";
    info += "Position (" + std::to_string(parameters[1]) + "," + std::to_string(parameters[2]) + "). ";
    info += "Player " + std::to_string(parameters[3]) + " | ";

    info += "Defender "+ objectTypeToString(parameters[4]) + ". ";
    info += "Position (" + std::to_string(parameters[5]) + "," + std::to_string(parameters[6]) + "). ";
    info += "Player " + std::to_string(parameters[7]);

    return info;
}

std::string LogAdapter::userUniteMessage(std::vector<int>& parameters) {
    std::string info = "User Unite | ";

    info += "First " + objectTypeToString(parameters[0]) + ". ";
    info += "Position (" + std::to_string(parameters[1]) + "," + std::to_string(parameters[2]) + "). ";
    info += "Player " + std::to_string(parameters[3]) + " | ";

    info += "Second "+ objectTypeToString(parameters[4]) + ". ";
    info += "Position (" + std::to_string(parameters[5]) + "," + std::to_string(parameters[6]) + "). ";
    info += "Player " + std::to_string(parameters[7]);

    return info;
}

std::string LogAdapter::userProduceMessage(std::vector<int>& parameters) {
    std::string info = "User Produce | ";

    info += "BASE at position ";
    info += "(" + std::to_string(parameters[0]) + "," + std::to_string(parameters[1]) + "). ";
    info += "Player " + std::to_string(parameters[2]) + " | ";
    info += "Produce " + objectTypeToString(parameters[3]);

    return info;
}
