#ifndef OOP_LOGPROXY_H
#define OOP_LOGPROXY_H

#include "Logging.h"
#include "../../Unit/Object/Object.h"

class Logging;
class Base;

/*
 * LogProxy -- класс, реализующий паттерн "прокси".
 * С помощью него происходит переключение режима логирования.
 */

class LogProxy
{
public:
    LogProxy();
    void logOff();
    void logInFile();
    void logInConsole();
    void logging(std::string& string);

    void loggingCreateBase(Base* base);
    void loggingCreateUnit(char id);
    void loggingGetUnit(Object* unit, int x, int y);
    void loggingMoveUnit(Object* unit, int x, int y, int i, int j);
    void loggingAttackUnit(Object* unit, int x, int y, int i, int j);

private:
    Logging* log;
    bool isOutput;
    bool isInFile;
    bool isInConsole;
};




#endif //OOP_LOGPROXY_H
