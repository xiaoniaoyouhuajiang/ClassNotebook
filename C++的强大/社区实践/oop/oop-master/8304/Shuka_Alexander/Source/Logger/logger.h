#ifndef LOGGER_H
#define LOGGER_H

#include <time.h>
#include <string>


enum class LVL : int
{
    INFO,
    DBG,
    WARNING,
    ERR
};


class Logger
{
public:
    virtual ~Logger() = default;

    virtual void writeToLog(const std::string& msg, LVL lvl = LVL::INFO) = 0;

protected:
    std::string getMsgLvl(LVL lvl) const;
    std::string getCurrentTime() const;
};

#endif // LOGGER_H
