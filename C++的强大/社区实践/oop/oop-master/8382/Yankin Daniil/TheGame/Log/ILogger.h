#pragma once

#include <string>


class ILogger
{
public:
    ILogger() = default;
    virtual ~ILogger() = default;
    virtual void log(std::string& info) = 0;
    virtual std::string getInfo() = 0;
};



enum LoggingDirection {
    LOGGING_DIR_NO,
    LOGGING_DIR_FILE,
    LOGGING_DIR_TERMINAL
};
