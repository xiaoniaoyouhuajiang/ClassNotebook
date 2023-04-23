//
// Created by Artem Butko on 21.05.2020.
//

#include "LoggingProxy.h"
#include "../Adapter/Adapter.h"

LoggingProxy::LoggingProxy()
{
    isInFile = false;
    isInConsole = false;
    isWorking = false;
    log = new Logging;
}

void LoggingProxy::loggingInConsole()
{
    isWorking = true;
    isInConsole = true;
    isInFile = false;
}

void LoggingProxy::loggingInFile()
{
    isWorking = true;
    isInConsole = false;
    isInFile = true;
}

void LoggingProxy::loggingOff()
{
    isWorking = false;
    isInConsole = false;
    isInFile = false;
    if (log->isOpen())
    {
        log->closeFile();
        log->setOpen(false);
    }
}

void LoggingProxy::logging(std::string &string)
{
    if (!isWorking) return;
    else if (isInConsole) log->loggingToConsole(string);
    else if (isInFile) log->loggingToFile(string);
}

void LoggingProxy::loggingCreateBase(Base *base)
{
    std::string string = Adapter::createBase(base);
    logging(string);
}

void LoggingProxy::loggingCreateUnit(char id)
{
    std::string string = Adapter::createUnit(id);
    logging(string);
}

void LoggingProxy::loggingGetUnit(Object *unit, int x, int y)
{
    std::string string = Adapter::getUnit(unit, x, y);
    logging(string);
}

void LoggingProxy::loggingMoveUnit(Object *unit, int x, int y, int i, int j)
{
    std::string string = Adapter::moveUnit(unit, x, y, i, j);
    logging(string);
}

void LoggingProxy::loggingAttackUnit(Object *unit, int x, int y, int i, int j)
{
    std::string string = Adapter::attackUnit(unit, x, y, i, j);
    logging(string);
}

