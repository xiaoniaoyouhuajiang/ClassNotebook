#ifndef LAB2_COMPLEXLOGGER_H
#define LAB2_COMPLEXLOGGER_H


#include "AbstractLogger.h"
#include "SimpleLogger.h"

class ComplexLogger : public AbstractLogger {
private:
    SimpleLogger* logger = nullptr;
public:
    ComplexLogger(SimpleLogger* logger) : AbstractLogger(logger->filename), logger(logger) {}
    bool write(std::string) override;
};


#endif
