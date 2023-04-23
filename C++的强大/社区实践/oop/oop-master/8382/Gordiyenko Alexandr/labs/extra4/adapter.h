#ifndef LABS_ADAPTER_H
#define LABS_ADAPTER_H
#include <string>
#include "LoggerProxy.h"

class Base;
class Unit;
class Field;


class Adapter : public LoggerProxy
{
    friend void operator<< (const Adapter& log, std::string str);

public:
    bool consoleWrite;
    bool fileWrite;

    Adapter(bool consoleWrite = true, bool fileWrite = false);

    void createField(Field *field);
    void createBase(Base *base);
    void createUnit(Unit *unit);
    void moveUnit(Unit *unit);

    void switchLog(std::string mod);

    void Log(const std::string &str) {
        std::ostringstream status;
        status << str;
        print(status.str(), consoleWrite, fileWrite);
    }

    void gameSaved();
    void gameLoaded();
};

#endif //LABS_ADAPTER_H
