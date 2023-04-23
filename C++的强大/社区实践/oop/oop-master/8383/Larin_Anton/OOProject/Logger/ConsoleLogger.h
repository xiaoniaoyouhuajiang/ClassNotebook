//
// Created by anton on 6/2/20.
//

#ifndef OOPROJECT_CONSOLELOGGER_H
#define OOPROJECT_CONSOLELOGGER_H

#include "iostream"

class ConsoleLogger {
public:
    void logToConsole(std::string str){
        std::cout<<"C_LOG: "<<str<<std::endl;
    }
};


#endif //OOPROJECT_CONSOLELOGGER_H
