#include "consolelogger.h"


void ConsoleLogger::writeToLog(const std::string& msg, LVL lvl)
{
    std::cout << getMsgLvl(lvl) + " " + msg + "\n";
}
