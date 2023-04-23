#include "loggerproxy.h"

LoggerProxy::LoggerProxy()
{

}

void LoggerProxy::unitCreation(Unit* unit, int x, int y, int baseNumb)
{
    std::string str = Adapter::unitCreation(unit, x, y, baseNumb);
    printLog(str);
}

void LoggerProxy::unitMoving(Unit *unit, int xx, int yy, int baseNumb)
{
    std::string str = Adapter::unitMoving(unit, xx, yy, baseNumb);
    printLog(str);
}

void LoggerProxy::baseCreation(Base* base)
{
    std::string str = Adapter::baseCreation(base);
    printLog(str);
}

void LoggerProxy::fieldCreation(GameField* field)
{
    std::string str = Adapter::fieldCreation(field);
    printLog(str);
}

void LoggerProxy::unitDeletion(Unit *unit, int x, int y)
{
    std::string str = Adapter::unitDeletion(unit, x, y);
    printLog(str);
}

void LoggerProxy::baseDestruction(Base* base)
{
    std::string str = Adapter::baseDestruction(base);
    printLog(str);
}

void LoggerProxy::baseDamage(Base* base)
{
    std::string str = Adapter::baseDamage(base);
    printLog(str);
}

void LoggerProxy::unitDamage(Unit *unit, int xx, int yy)
{
    std::string str = Adapter::unitDamage(unit, xx ,yy);
    printLog(str);
}

void LoggerProxy::printLog(std::string &str)
{
    if (isLog){
        if (toFile)
            Logger::printLogFile(str);
        else
            Logger::printLogConsole(str);
    }
}

void LoggerProxy::offLog()
{
    isLog = false;
    if (Logger::fileIsOpen){
        Logger::fileIsOpen = false;
        Logger::file->~File();
    }
}

void LoggerProxy::logToFile()
{
    isLog = true;
    toFile = true;
}

void LoggerProxy::logToConsole()
{
    isLog = true;
    toFile = false;
}

bool LoggerProxy::isOn()
{
    return isLog;
}
