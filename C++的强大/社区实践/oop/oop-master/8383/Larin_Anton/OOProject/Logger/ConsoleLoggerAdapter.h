//
// Created by anton on 6/2/20.
//

#ifndef OOPROJECT_CONSOLELOGGERADAPTER_H
#define OOPROJECT_CONSOLELOGGERADAPTER_H

#include "AbstractLogger.h"

#include "ConsoleLogger.h"

class ConsoleLoggerAdapter:public ConsoleLogger,public AbstractLogger{
public:
    void log(std::string str) override {
        logToConsole(str);
    }
};

#endif //OOPROJECT_CONSOLELOGGERADAPTER_H
