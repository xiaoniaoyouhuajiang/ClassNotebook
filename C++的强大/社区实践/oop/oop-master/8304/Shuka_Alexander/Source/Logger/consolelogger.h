#ifndef CONSOLELOGGER_H
#define CONSOLELOGGER_H

#include <iostream>

#include "logger.h"


class ConsoleLogger : public Logger
{
public:
    explicit ConsoleLogger() = default;

    virtual void writeToLog(const std::string& msg, LVL lvl = LVL::INFO) override;
};

#endif // CONSOLELOGGER_H
