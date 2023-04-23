#ifndef FILELOGGER_H
#define FILELOGGER_H

#include <fstream>
#include <cstdio>

#include "logger.h"


class FileLogger : public Logger
{
public:
    explicit FileLogger(const std::string& fileName);

    virtual void writeToLog(const std::string& msg, LVL lvl = LVL::INFO) override;

private:
    std::string fileName;
};

#endif // FILELOGGER_H
