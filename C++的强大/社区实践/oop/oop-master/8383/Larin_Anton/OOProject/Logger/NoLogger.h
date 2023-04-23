//
// Created by anton on 6/2/20.
//

#ifndef OOPROJECT_NOLOGGER_H
#define OOPROJECT_NOLOGGER_H

#include "AbstractLogger.h"

class NoLogger: public AbstractLogger {
    void log(std::string str) override {

    }
};


#endif //OOPROJECT_NOLOGGER_H
