#pragma once

#include "LoggerFormat.h"
#include "Logger.h"
#include "NoLogging.h"
#include <string>

using namespace std;

class LoggerProxy {
public:
    LoggerProxy();
    ~LoggerProxy();
    void setLogger(Logger* logger);
    void setFormat(LogFormatter* formatter);
    friend LoggerProxy& operator<<(LoggerProxy& logger, const string& str);
    friend LoggerProxy& operator<<(LoggerProxy& logger, const unsigned value);
    friend LoggerProxy& operator<<(LoggerProxy& logger, const Logger::Endl&);

private:
    Logger* logger;
    LogFormatter* formatter;
    bool printFormatted = true;

    void log(const string& str);
};