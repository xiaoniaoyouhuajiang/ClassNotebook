#include "LoggerProxy.h"

LoggerProxy::LoggerProxy(uint16_t loggingDirection) : logger(nullptr), loggingDirection(loggingDirection) {
    if (loggingDirection == LOGGING_DIR_FILE) {
        try {
            logger = new FileLogger("GameLog.txt");
        }
        catch(std::runtime_error error) {
            logger = nullptr;
            loggingDirection = LOGGING_DIR_NO;
        }
    }
    else if (loggingDirection == LOGGING_DIR_TERMINAL) {
        logger = new TerminalLogger();
    }
}

LoggerProxy::~LoggerProxy() {
    if (logger != nullptr) {
        delete logger;
        logger = nullptr;
    }
}



void LoggerProxy::log(std::string& info) {
    if (logger != nullptr) {
        logger->log(info);
    }
}

std::string LoggerProxy::getInfo() {
    if (logger != nullptr) {
        return logger->getInfo();
    }
    return std::string();
}

void LoggerProxy::setLoggingDirection(uint16_t loggingDirection) {
    if (this->loggingDirection == loggingDirection) {
        return;
    }

    delete logger;
    logger = nullptr;
    this->loggingDirection = loggingDirection;

    if (loggingDirection == LOGGING_DIR_FILE) {
        try {
            logger = new FileLogger("GameLog.txt");
        }
        catch(std::runtime_error error) {
            logger = nullptr;
            loggingDirection = LOGGING_DIR_NO;
        }
    }
    else if (loggingDirection == LOGGING_DIR_TERMINAL) {
        logger = new TerminalLogger();
    }
}
