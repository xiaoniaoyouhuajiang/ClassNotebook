#include <string>
#include "LogProxy.h"
#include "Adapter.h"


LogProxy::LogProxy()
{
    isInFile = false;
    isInConsole = false;
    isOutput = false;
    log = new Logging;
}

void LogProxy::logInConsole()
{
    isOutput = true;
    isInConsole = true;
    isInFile = false;
}

void LogProxy::logInFile()
{
    isOutput = true;
    isInConsole = false;
    isInFile = true;
}

void LogProxy::logOff()
{
    isOutput = false;
    isInConsole = false;
    isInFile = false;
    if (log->isOpen())
    {
        log->closeFile();
        log->setOpen(false);
    }
}

void LogProxy::logging(std::string &string)
{
    if (!isOutput) return;
    else if (isInConsole) log->loggingToConsole(string);
    else if (isInFile) log->loggingToFile(string);
}

void LogProxy::loggingCreateBase(Base *base)
{
    std::string string = Adapter::createBase(base);
    logging(string);
}

void LogProxy::loggingCreateUnit(char id)
{
    std::string string = Adapter::createUnit(id);
    logging(string);
}

void LogProxy::loggingGetUnit(Object *unit, int x, int y)
{
    std::string string = Adapter::getUnit(unit, x, y);
    logging(string);
}

void LogProxy::loggingMoveUnit(Object *unit, int x, int y, int i, int j)
{
    std::string string = Adapter::moveUnit(unit, x, y, i, j);
    logging(string);
}

void LogProxy::loggingAttackUnit(Object *unit, int x, int y, int i, int j)
{
    std::string string = Adapter::attackUnit(unit, x, y, i, j);
    logging(string);
}