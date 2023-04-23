#ifndef LABS_LOGGERPROXY_H
#define LABS_LOGGERPROXY_H

#include <string>
#include <iostream>
#include "LogSwitch.h"
#include "../extra5/RAII.h"

class LoggerProxy: LogSwitch{

public:
    LoggerProxy(){
    }

protected:
    void print(std::string log, bool consoleWrite, bool fileWrite){
        if (consoleWrite){
            printConsole(log);
        }
        if (fileWrite) {
            printFile(log);
        }
    }
};

#endif //LABS_LOGGERPROXY_H
