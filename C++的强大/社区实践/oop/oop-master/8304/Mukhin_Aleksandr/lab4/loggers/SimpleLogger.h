#ifndef LAB2_SIMPLELOGGER_H
#define LAB2_SIMPLELOGGER_H

#include <fstream>
#include <iostream>
#include "AbstractLogger.h"

class SimpleLogger : public AbstractLogger {
public:
    SimpleLogger();
    explicit SimpleLogger(std::string filename) : AbstractLogger(filename) {
        output << "Start recording!" << std::endl;
    }
    bool write(std::string) override;
    ~SimpleLogger();
};


#endif
