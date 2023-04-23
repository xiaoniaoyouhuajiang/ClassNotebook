//
// Created by shenk on 24.03.2020.
//

#ifndef UNTITLED13_TERMINALLOGGER_H
#define UNTITLED13_TERMINALLOGGER_H

#include <iostream>
#include "Logger.h"

class TerminalLogger: public Logger {

public:

    void log(std::string &s) override{

        std::cout << s;

    }


};


#endif //UNTITLED13_TERMINALLOGGER_H
