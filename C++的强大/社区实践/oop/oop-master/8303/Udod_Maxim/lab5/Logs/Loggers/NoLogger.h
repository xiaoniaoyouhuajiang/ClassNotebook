//
// Created by shenk on 24.03.2020.
//

#ifndef UNTITLED13_NOLOGGER_H
#define UNTITLED13_NOLOGGER_H

#include "Logger.h"

class NoLogger: public Logger {

public:

    void log(std::string &s) override{

        return;

    }


};


#endif //UNTITLED13_NOLOGGER_H
