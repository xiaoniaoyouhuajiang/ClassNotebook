#pragma once

#include <iostream>
#include <ostream>
#include <fstream>
#include "ILogger.h"
#include "Time.h"


class FileLogger : public ILogger
{
public:
    FileLogger(std::string logFileName);
    ~FileLogger() override;
    void log(std::string& info) override;
    std::string getInfo() override;

    friend std::ostream& operator<<(std::ostream& stream, ILogger& logger);

private:
    std::string info;
    std::ofstream fileStream;
    Time time;
};



class TerminalLogger : public ILogger
{
public:
    TerminalLogger();
    void log(std::string& info) override;
    std::string getInfo() override;

    friend std::ostream& operator<<(std::ostream& stream, ILogger& logger);

private:
    std::string info;
    Time time;
};
