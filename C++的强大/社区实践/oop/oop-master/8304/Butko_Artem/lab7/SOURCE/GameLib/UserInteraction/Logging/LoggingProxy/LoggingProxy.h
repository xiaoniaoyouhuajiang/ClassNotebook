//
// Created by Artem Butko on 21.05.2020.
//

#ifndef OOP_NEW_LOGGINGPROXY_H
#define OOP_NEW_LOGGINGPROXY_H


#include "../Logging.h"
#include "../../../Objects/Base/Base.h"

class Logging;
class Base;

/*
 * LoggingProxy -- класс, реализующий паттерн "прокси".
 * С помощью него происходит переключение режима логирования.
 */

class LoggingProxy
{
public:
    LoggingProxy();
    void loggingOff();
    void loggingInFile();
    void loggingInConsole();
    void logging(std::string& string);

    void loggingCreateBase(Base* base);
    void loggingCreateUnit(char id);
    void loggingGetUnit(Object* unit, int x, int y);
    void loggingMoveUnit(Object* unit, int x, int y, int i, int j);
    void loggingAttackUnit(Object* unit, int x, int y, int i, int j);

private:
    Logging* log;
    bool isWorking;
    bool isInFile;
    bool isInConsole;
};


#endif //OOP_NEW_LOGGINGPROXY_H
