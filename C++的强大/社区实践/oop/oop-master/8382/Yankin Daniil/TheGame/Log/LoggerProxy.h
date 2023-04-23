#pragma once

#include "Logger.h"


class LoggerProxy : public ILogger
{
public:
    LoggerProxy(uint16_t loggingDirection);
    ~LoggerProxy() override;

    void log(std::string& info) override;
    std::string getInfo() override;
    void setLoggingDirection(uint16_t loggingDirection);

private:
    ILogger* logger;
    uint16_t loggingDirection;
};
