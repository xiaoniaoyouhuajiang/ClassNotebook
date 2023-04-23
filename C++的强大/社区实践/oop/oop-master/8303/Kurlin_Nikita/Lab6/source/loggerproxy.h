#ifndef LOGGERPROXY_H
#define LOGGERPROXY_H

#include "Units/unit.h"
#include "adapter.h"
#include "logger.h"

class LoggerProxy
{
    static bool isLog;
    static bool toFile;
    static void printLog(std::string&);

public:
    LoggerProxy();
    static void unitCreation(Unit*, int, int, int);
    static void unitMoving(Unit*, int, int, int);
    static void baseCreation(Base*);
    static void fieldCreation(GameField*);
    static void unitDeletion(Unit*, int, int);
    static void baseDestruction(Base*);
    static void baseDamage(Base*);
    static void unitDamage(Unit*, int, int);
    static void offLog();
    static void logToFile();
    static void logToConsole();
    static bool isOn();
};

#endif // LOGGERPROXY_H
