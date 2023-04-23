#include "logger.h"


std::string Logger::getMsgLvl(LVL lvl) const
{
    auto time = getCurrentTime();
    time.pop_back();

    if (lvl == LVL::DBG) {
        return "DEBUG(" + time + "): ";
    }
    else if (lvl == LVL::INFO) {
        return "INFO(" + time + "): ";
    }
    else if (lvl == LVL::ERR) {
        return "ERROR(" + time + "): ";
    }

    return "WARNING(" + time + "): ";
}


std::string Logger::getCurrentTime() const
{
    auto currentTime = time(nullptr);

    return asctime(localtime(&currentTime));
}
